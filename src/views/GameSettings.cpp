#include "GameSettings.hpp"
#include "Helper.hpp"
#include "Settings.hpp"
#include <iostream>
#include "WindowAnchorHandler.hpp"
#include "ObservableIntValuePresenter.hpp"
#include "ObservableUlongValuePresenter.hpp"
#include "ObservableColorValuePresenter.hpp"
#include "ObservableRestrictedValuePresenter.hpp"
#include "Rectangle.hpp"

namespace {
  color::COLOR_SCHEME_TYPE key_color_scheme = {
    { color::ColorSchemeID::BackgroundColor, 0UL },
    { color::ColorSchemeID::FrameColor, ~0UL },
    { color::ColorSchemeID::TextColor, (255UL << 16) }
  };

  color::COLOR_SCHEME_TYPE value_color_scheme = {
    { color::ColorSchemeID::BackgroundColor, 0UL },
    { color::ColorSchemeID::FrameColor, ~0UL },
    { color::ColorSchemeID::TextColor, (127UL << 16)|(255UL << 8)|212UL }
  };

  color::COLOR_SCHEME_TYPE menu_color_scheme = {
    { color::ColorSchemeID::BackgroundColor, 0UL },
    { color::ColorSchemeID::FrameColor, ~0UL }
  };
}

namespace views {
  GameSettings::Setting::Setting(std::unique_ptr<abstractions::ui::TextLabel> key_presenter, 
                                 std::unique_ptr<abstractions::ui::Object> value_presenter,
                                 xlib::X11_Window* x_window) 
  : xlib::X11_Menu(::ui::LayoutType::HORIZONTAL, {}, menu_color_scheme, 30U) {
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
  , menu(ui::LayoutType::VERTICAL, {}, color::COLOR_SCHEME_TYPE(), 20U) {

    auto snake_speed = configuration::Settings::get_concrete_ptr<configuration::RESTRICTED_ULONG>(configuration::ConfigID::SNAKE_SPEED);
    auto snake_color = configuration::Settings::get_concrete_ptr<color::ColorPallete>(configuration::ConfigID::SNAKE_COLOR);
    auto snake_x = configuration::Settings::get_concrete_ptr<configuration::RESTRICTED_INT>(configuration::ConfigID::SNAKE_HEAD_X);
    auto snake_y = configuration::Settings::get_concrete_ptr<configuration::RESTRICTED_INT>(configuration::ConfigID::SNAKE_HEAD_Y);
    auto snake_width = configuration::Settings::get_concrete_ptr<configuration::RESTRICTED_UINT>(configuration::ConfigID::SNAKE_HEAD_WIDTH);
    auto snake_height = configuration::Settings::get_concrete_ptr<configuration::RESTRICTED_UINT>(configuration::ConfigID::SNAKE_HEAD_HEIGHT);

    std::unique_ptr<xlib::X11_TextLabel> text_label(new xlib::X11_TextLabel(std::to_string(snake_speed->get_value().get_restricted_value()), {}, value_color_scheme));
    std::unique_ptr<xlib::X11_ColorLabel> color_label(new xlib::X11_ColorLabel(snake_color->get_value(), geometry::Rectangle{.width = 100U, .height = text_label->get_height()}, value_color_scheme));

    menu.add_item(std::move(construct_menu_item<ui::ObservableRestrictedValuePresenter<decltype(snake_speed->get_value().get_restricted_value())>, decltype(snake_speed), xlib::X11_TextLabel> (
            "Snake speed: ", snake_speed, key_color_scheme, value_color_scheme, std::move(text_label), x_window)));

    menu.add_item(std::move(construct_menu_item<ui::ObservableColorValuePresenter, decltype(snake_color), xlib::X11_ColorLabel>(
            "Snake color: ", snake_color,  key_color_scheme, value_color_scheme, std::move(color_label), x_window)));

    text_label.reset(new xlib::X11_TextLabel(std::to_string(snake_x->get_value().get_restricted_value()), {}, value_color_scheme));
    menu.add_item(std::move(construct_menu_item<ui::ObservableRestrictedValuePresenter<decltype(snake_x->get_value().get_restricted_value())>, decltype(snake_x), xlib::X11_TextLabel> (
            "Snake X: ", snake_x, key_color_scheme, value_color_scheme, std::move(text_label), x_window)));

    text_label.reset(new xlib::X11_TextLabel(std::to_string(snake_y->get_value().get_restricted_value()), {}, value_color_scheme));
    menu.add_item(std::move(construct_menu_item<ui::ObservableRestrictedValuePresenter<decltype(snake_y->get_value().get_restricted_value())>, decltype(snake_y), xlib::X11_TextLabel> (
            "Snake Y: ", snake_y, key_color_scheme, value_color_scheme, std::move(text_label), x_window)));

    text_label.reset(new xlib::X11_TextLabel(std::to_string(snake_width->get_value().get_restricted_value()), {}, value_color_scheme));
    menu.add_item(std::move(construct_menu_item<ui::ObservableRestrictedValuePresenter<decltype(snake_width->get_value().get_restricted_value())>, decltype(snake_width), xlib::X11_TextLabel> (
            "Snake WIDTH: ", snake_width, key_color_scheme, value_color_scheme, std::move(text_label), x_window)));

    text_label.reset(new xlib::X11_TextLabel(std::to_string(snake_height->get_value().get_restricted_value()), {}, value_color_scheme));
    menu.add_item(std::move(construct_menu_item<ui::ObservableRestrictedValuePresenter<decltype(snake_height->get_value().get_restricted_value())>, decltype(snake_height), xlib::X11_TextLabel> (
            "Snake HEIGHT: ", snake_height, key_color_scheme, value_color_scheme, std::move(text_label), x_window)));
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
      case XK_minus: if(mask != 0u) break;
      case XK_Left:
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
