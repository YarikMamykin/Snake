#include "GameSettings.hpp"
#include "Helper.hpp"
#include "Settings.hpp"
#include <iostream>

namespace {
  xlib::X11_TextLabel::ColorScheme key_color_scheme = {
    .background = 0UL,
    .frame = ~0UL, 
    .text = (255UL << 16) 
  };

  xlib::X11_TextLabel::ColorScheme value_color_scheme = {
    .background = 0UL,
    .frame = ~0UL, 
    .text = (127UL << 16)|(255UL << 8)|212UL
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
}

namespace views {

  GameSettings::GameSettings(xlib::X11_Window* x_window) 
  : x_window(x_window) 
  , key_labels_layout({.x = 100, .y = 100})
  , value_labels_layout({.x = 500, .y = 100}) {
    settings_items.emplace_back(Setting("Snake speed: ", settings::Settings::settings().snake_speed, x_window));
    settings_items.emplace_back(Setting("Snake color: ", 255U, x_window));

    settings_items.begin()->set_active(true);
    current_active_item = settings_items.begin();

    for(auto& item : settings_items) {
      key_labels_layout.add(&(item.key_label));
      value_labels_layout.add(&(item.value_label));
    }
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
    }

    update();
  }

  void GameSettings::update() {
    key_labels_layout.update();
    value_labels_layout.update();
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
}
