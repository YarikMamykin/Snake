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
    auto snake_size = configuration::Settings::get_concrete_ptr<configuration::RESTRICTED_UINT>(configuration::ConfigID::SNAKE_SIZE);
    auto food_color = configuration::Settings::get_concrete_ptr<color::ColorPallete>(configuration::ConfigID::FOOD_COLOR);

    std::unique_ptr<xlib::X11_TextLabel> text_label(new xlib::X11_TextLabel(std::to_string(snake_speed->get_value().get_restricted_value()), {}, value_color_scheme));
    auto&& items_height = text_label->get_height();
    std::unique_ptr<xlib::X11_ColorLabel> color_label(new xlib::X11_ColorLabel(snake_color->get_value(), geometry::Rectangle{.width = 100U, .height = items_height }, value_color_scheme));

    menu.add_item(std::move(construct_menu_item<ui::ObservableRestrictedValuePresenter<decltype(snake_speed->get_value().get_restricted_value())>, decltype(snake_speed), xlib::X11_TextLabel> (
            "Snake speed: ", snake_speed, key_color_scheme, value_color_scheme, std::move(text_label), x_window)));

    menu.add_item(std::move(construct_menu_item<ui::ObservableColorValuePresenter, decltype(snake_color), xlib::X11_ColorLabel>(
            "Snake color: ", snake_color,  key_color_scheme, value_color_scheme, std::move(color_label), x_window)));

    text_label.reset(new xlib::X11_TextLabel(std::to_string(snake_size->get_value().get_restricted_value()), {}, value_color_scheme));
    menu.add_item(std::move(construct_menu_item<ui::ObservableRestrictedValuePresenter<decltype(snake_size->get_value().get_restricted_value())>, decltype(snake_size), xlib::X11_TextLabel> (
            "Snake size: ", snake_size, key_color_scheme, value_color_scheme, std::move(text_label), x_window)));

    color_label.reset(new xlib::X11_ColorLabel(food_color->get_value(), geometry::Rectangle{.width = 100U, .height = items_height }, value_color_scheme));
    menu.add_item(std::move(construct_menu_item<ui::ObservableColorValuePresenter, decltype(food_color), xlib::X11_ColorLabel>(
            "Food color: ", food_color,  key_color_scheme, value_color_scheme, std::move(color_label), x_window)));
  }

  GameSettings::~GameSettings() {
  }

  void GameSettings::activate() {
    update();
  }

  void GameSettings::handle_key_press(const KeySym&& key_sym, const unsigned int&& mask) {
    switch(key_sym) {
      case XK_Escape: helpers::Helper::SendChangeViewEvent(views::ViewID::MENU); break;
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
