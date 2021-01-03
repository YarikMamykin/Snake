#include "GameSettings.hpp"
#include "Helper.hpp"
#include "Settings.hpp"
#include <iostream>
#include "WindowAnchorHandler.hpp"
#include "UlongValuePresenter.hpp"
#include "ColorValuePresenter.hpp"

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

  abstractions::ui::COLOR_SCHEME_TYPE menu_color_scheme = {
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
  , menu(ui::LayoutType::VERTICAL, {}, abstractions::ui::COLOR_SCHEME_TYPE(), x_window, 20U) {

    std::unique_ptr<xlib::X11_TextLabel> text_label(new xlib::X11_TextLabel(std::to_string(settings::Settings::settings().snake_speed), {}, value_color_scheme, x_window));
    std::unique_ptr<xlib::X11_ColorLabel> color_label(new xlib::X11_ColorLabel(0UL, {.width = 100U, .height = text_label->get_height()}, value_color_scheme, x_window));

    menu.add_item(std::move(construct_menu_item<ui::UlongValuePresenter, 
                                                unsigned long, 
                                                xlib::X11_TextLabel>(
            "Snake speed: ", 
            settings::Settings::settings().snake_speed, 
            key_color_scheme,
            value_color_scheme,
            std::move(text_label),
            x_window)));

    menu.add_item(std::move(construct_menu_item<ui::ColorValuePresenter, 
                                                abstractions::ui::ColorLabel::Color, 
                                                xlib::X11_ColorLabel>(
            "Snake color: ", 
            settings::Settings::settings().snake_color, 
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

  void GameSettings::handle_key_press(const KeySym&& key_sym) {
    switch(key_sym) {
      case XK_Escape: helpers::Helper::SendChangeViewEvent(x_window, views::ViewID::MENU); break;
      case XK_Down: menu.move_to_next_item(); break;
      case XK_Up: menu.move_to_prev_item(); break;
      case XK_KP_Add: static_cast<GameSettings::Setting*>(menu.get_current_item()->get())->increase(); break;
      case XK_KP_Subtract: static_cast<GameSettings::Setting*>(menu.get_current_item()->get())->decrease(); break;
    }

    update();
  }

  void GameSettings::update() {
    ui::WindowAnchorHandler<decltype(menu)> anchor_handler(&menu, x_window);
    menu.get_current_item()->get()->set_focused(true);
    menu.show(true);
  }

}
