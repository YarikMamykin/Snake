#include "GameSettings.hpp"
#include "Helper.hpp"
#include "Settings.hpp"
#include <iostream>
#include "WindowAnchorHandler.hpp"

namespace {
  abstractions::ui::COLOR_SCHEME_TYPE key_color_scheme = {
    { ui::ColorSchemeID::BackgroundColor, 0UL },
    { ui::ColorSchemeID::FrameColor, ~0UL },
    { ui::ColorSchemeID::TextColor, (255UL << 16) }
  };

  abstractions::ui::COLOR_SCHEME_TYPE value_color_scheme = {
    { ui::ColorSchemeID::BackgroundColor, 0UL },
    { ui::ColorSchemeID::FrameColor, ~0UL },
    { ui::ColorSchemeID::TextColor, (127UL << 16)|(255UL << 8)|212UL }
  };
}

namespace views {
  GameSettings::Setting::Setting(const std::string& key, unsigned int value, xlib::X11_Window* parent_window) 
  : key(key)
  , value(value)
  , key_label(key, {}, key_color_scheme, parent_window)
  , value_label(std::to_string(value), {}, value_color_scheme, parent_window) { }

  void GameSettings::Setting::set_active(bool active) {
    this->active = active;
    key_label.set_focused(this->active);
    value_label.set_focused(this->active);  
  }

  void GameSettings::Setting::update_value(const unsigned int& new_value) {
    value = new_value;
    value_label.set_text(std::to_string(new_value));
  }
}

namespace views {

  GameSettings::GameSettings(xlib::X11_Window* x_window) 
  : x_window(x_window) 
  , horizontal_layout({}) {
    settings_items.emplace_back(Setting("Snake speed: ", settings::Settings::settings().snake_speed, x_window));
    settings_items.emplace_back(Setting("Snake color: ", settings::Settings::settings().snake_color, x_window));

    settings_items.front().set_active(true);
    current_active_item = settings_items.begin();

    for(auto& item : settings_items) {
      auto&& layout = LAYOUT_TYPE({});
      layout.add(&(item.key_label));
      layout.add(&(item.value_label));
      labels_layout.push_back(layout);
      horizontal_layout.add(&labels_layout.back());
    }
    ui::WindowAnchorHandler<V_LAYOUT_TYPE> anchor_handler(&horizontal_layout, x_window);
  }

  GameSettings::~GameSettings() {
  }

  void GameSettings::activate() {
    update();
  }

  void GameSettings::deactivate() {
  }

  void GameSettings::handle_key_press(const KeySym&& key_sym) {
    switch(key_sym) {
      case XK_Escape: helpers::Helper::SendChangeViewEvent(x_window, views::ViewID::MENU); break;
      case XK_Down: move_to_next_item(); break;
      case XK_Up: move_to_prev_item(); break;
      case XK_KP_Add: increase_setting_value(); break;
      case XK_KP_Subtract: decrease_setting_value(); break;
    }

    update();
  }

  void GameSettings::update() {
    horizontal_layout.update();
  }

  void GameSettings::move_to_next_item() {
    for(auto& item : settings_items) {
      item.set_active(false);
    }

    if(current_active_item == --settings_items.end()) {
      settings_items.begin()->set_active(true);
      current_active_item = settings_items.begin();
      return;
    }

    current_active_item = std::next(current_active_item);
    current_active_item->set_active(true);
    return;
  }

  void GameSettings::move_to_prev_item() {
    for(auto& item : settings_items) {
      item.set_active(false);
    }

    if(current_active_item == settings_items.begin()) {
      settings_items.back().set_active(true);
      current_active_item = --settings_items.end();
      return;
    }

    current_active_item = std::prev(current_active_item);
    current_active_item->set_active(true);
    return;
  }

  void GameSettings::increase_setting_value() {
    current_active_item->update_value(current_active_item->value + 1U);
  }

  void GameSettings::decrease_setting_value() {
    current_active_item->update_value(current_active_item->value - 1U);
  }
}
