#include "GameSettings.hpp"
#include "Helper.hpp"
#include "Settings.hpp"
#include <iostream>
#include <array>

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
  , key_label(key, {.x = 100, .y = 100}, key_color_scheme, parent_window)
  , value_label(std::to_string(value), {.x = key_label.get_x() + key_label.get_width() + 10U, .y = 100}, value_color_scheme, parent_window) { }

  void GameSettings::Setting::show() {
    key_label.show();
    value_label.show();
  }

}

namespace views {

  GameSettings::GameSettings(xlib::X11_Window* x_window) 
  : x_window(x_window) {
    settings_items.emplace_back(Setting("Snake speed: ", settings::Settings::settings().snake_speed, x_window));
  }

  GameSettings::~GameSettings() {
  }

  void GameSettings::activate() {
    for(auto& item : settings_items) {
      item.show();
    }
  }

  void GameSettings::deactivate() {
  }

  void GameSettings::handle_key_press(const KeySym&& key_sym) {
    switch(key_sym) {
      case XK_Escape: helpers::Helper::SendChangeViewEvent(x_window, views::ViewID::MENU); break;
    }
    // switch(key_sym) {
      // case XK_Down:
        // {
          // const auto& active_item = std::find_if(items.begin(), items.end(), [](const Item& item) { return item.active; });
          // for(auto& item : items) {
            // item.hide_focus();
          // }

          // if(active_item == --items.end()) {
            // items.begin()->show_focus();
            // break;
          // }

          // std::next(active_item)->show_focus();
          // break;
        // }
      // case XK_Up:
        // {
          // auto active_item = std::find_if(items.begin(), items.end(), [](const Item& item) { return item.active; });
          // for(auto& item : items) {
            // item.hide_focus();
          // }

          // if(active_item == items.begin()) {
            // items.back().show_focus();
            // return;
          // }

          // std::prev(active_item)->show_focus();
          // break;
        // }
      // case XK_Return:
        // {
          // for(auto& item : items) {
            // item.handle_key_press(std::move(key_sym));
          // }
          // break;
        // }
    // }
  }

  const int GameSettings::get_event_handling_mask() const {
    return events::KeyPressHandler::mask;
  }
}
