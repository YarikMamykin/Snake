#include "GameSettings.hpp"
#include "Helper.hpp"
#include "Settings.hpp"
#include <iostream>
#include "WindowAnchorHandler.hpp"
#include "UlongValuePresenter.hpp"
#include "ColorValuePresenter.hpp"

namespace {
  constants::COLOR_SCHEME_TYPE key_color_scheme = {
    { ui::ColorSchemeID::BackgroundColor, 0UL },
    { ui::ColorSchemeID::FrameColor, ~0UL },
    { ui::ColorSchemeID::TextColor, (255UL << 16) }
  };

  constants::COLOR_SCHEME_TYPE value_color_scheme = {
    { ui::ColorSchemeID::BackgroundColor, 0UL },
    { ui::ColorSchemeID::FrameColor, ~0UL },
    { ui::ColorSchemeID::TextColor, (127UL << 16)|(255UL << 8)|212UL }
  };

  constants::COLOR_SCHEME_TYPE menu_color_scheme = {
    { ui::ColorSchemeID::BackgroundColor, 0UL },
    { ui::ColorSchemeID::FrameColor, ~0UL }
  };
}

namespace views {
  GameSettings::Setting::Setting(std::unique_ptr<abstractions::ui::TextLabel> key_presenter, 
                                 std::unique_ptr<abstractions::ui::Object> value_presenter,
                                 xlib::X11_Window* x_window) 
  : xlib::X11_Menu(::ui::LayoutType::HORIZONTAL, {}, menu_color_scheme, x_window, 30U) {
    add_item(std::move(key_presenter));
    add_item(std::move(value_presenter));
    margin = 0U;
  }

  void GameSettings::Setting::increase() {
    increase_binder();
  }

  void GameSettings::Setting::decrease() {
    decrease_binder();
  }
}

namespace views {

  GameSettings::GameSettings(xlib::X11_Window* x_window) 
  : x_window(x_window)  
  , menu(ui::LayoutType::VERTICAL, {}, constants::COLOR_SCHEME_TYPE(), x_window, 20U) {

    std::unique_ptr<xlib::X11_TextLabel> text_label(new xlib::X11_TextLabel(std::to_string(configuration::Settings().snake_speed), {}, value_color_scheme, x_window));
    std::unique_ptr<xlib::X11_ColorLabel> color_label(new xlib::X11_ColorLabel(0UL, {.width = 100U, .height = text_label->get_height()}, value_color_scheme, x_window));

    menu.add_item(std::move(construct_menu_item<ui::UlongValuePresenter, 
                                                unsigned long, 
                                                xlib::X11_TextLabel>(
            "Snake speed: ", 
            configuration::Settings().snake_speed, 
            key_color_scheme,
            value_color_scheme,
            std::move(text_label),
            x_window)));

    menu.add_item(std::move(construct_menu_item<ui::ColorValuePresenter, 
                                                color::Color, 
                                                xlib::X11_ColorLabel>(
            "Snake color: ", 
            configuration::Settings().snake_color, 
            key_color_scheme,
            value_color_scheme,
            std::move(color_label),
            x_window)));
  }

  GameSettings::~GameSettings() {
  }

  void GameSettings::activate() {
    update();
  }

  void GameSettings::deactivate() {
  }

  void GameSettings::handle_key_press(const KeySym&& key_sym, const unsigned int&& mask) {
    switch(key_sym) {
      case XK_Escape: helpers::Helper::SendChangeViewEvent(x_window, views::ViewID::MENU); break;
      case XK_Down: menu.move_to_next_item(); break;
      case XK_Up: menu.move_to_prev_item(); break;
      case XK_equal: if(!(mask & ShiftMask)) break;
      case XK_Right:
      case XK_KP_Add: current_item_as_setting(menu)->increase(); break;
      case XK_Left:
      case XK_minus: if(mask == 0u) break;
      case XK_KP_Subtract: current_item_as_setting(menu)->decrease(); break;
    }

    update();
  }

  void GameSettings::update() {
    ui::WindowAnchorHandler<decltype(menu)> anchor_handler(&menu, x_window);
    menu.get_current_item()->get()->set_focused(true);
    menu.show(true);
  }

  GameSettings::Setting* GameSettings::current_item_as_setting(const xlib::X11_Menu& menu) {
    return static_cast<GameSettings::Setting*>(menu.get_current_item()->get());
  }
}
