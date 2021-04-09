#include "views/GameSettings.hpp"
#include "helpers/Helper.hpp"
#include "configuration/Settings.hpp"
#include "anchor_handlers/CenterWindowAnchorHandler.hpp"
#include "geometry/Rectangle.hpp"
#include "ui/ColorValuePresenter.hpp"
#include "abstractions/ui/RestrictedValuePresenter.hpp"

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
                                 std::function<void()> increase_binder, 
                                 std::function<void()> decrease_binder)
  : xlib::X11_Menu(::ui::LayoutType::HORIZONTAL, {}, menu_color_scheme, 30U) 
  , increase_binder(increase_binder)
  , decrease_binder(decrease_binder) {
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

  GameSettings::GameSettings() 
  : menu(new xlib::X11_Menu(ui::LayoutType::VERTICAL, {}, color::COLOR_SCHEME_TYPE(), 20U)) {

    auto& snake_speed_shared = config::get_concrete_ref<configuration::RESTRICTED_ULONG>(config_id::SNAKE_SPEED);
    auto snake_speed = snake_speed_shared.get_restricted_value();

    auto& snake_color = config::get_concrete_ref<color::ColorPallete>(config_id::SNAKE_COLOR);

    auto& snake_size_shared = config::get_concrete_ref<configuration::RESTRICTED_UINT>(config_id::SNAKE_SIZE);
    auto snake_size = snake_size_shared.get_restricted_value();

    auto food_color = config::get_concrete_ref<color::ColorPallete>(config_id::FOOD_COLOR);

    auto setting_builder = [](const std::string&& name, std::unique_ptr<abstractions::ui::Object> value_presenter, const color::COLOR_SCHEME_TYPE& key_color_scheme) -> std::unique_ptr<Setting> {
      std::unique_ptr<abstractions::ui::TextLabel> key_presenter(new xlib::X11_TextLabel(name, {}, key_color_scheme));
      auto increase_binder = dynamic_cast<abstractions::ui::ValuePresenter*>(value_presenter.get())->bind_increase_value_trigger();
      auto decrease_binder = dynamic_cast<abstractions::ui::ValuePresenter*>(value_presenter.get())->bind_decrease_value_trigger();
      return std::make_unique<Setting>(std::move(key_presenter), std::move(value_presenter), increase_binder, decrease_binder);
    };

    auto text_label = std::make_unique<xlib::X11_TextLabel>(std::to_string(snake_speed), geometry::Rectangle{}, value_color_scheme);
    auto&& items_height = text_label->get_height();

    menu->add_item(setting_builder(
          "Snake speed: ", 
          std::make_unique<abstractions::ui::RestrictedValuePresenter<decltype(snake_speed)>>(config_id::SNAKE_SPEED, std::move(text_label)),
          key_color_scheme));
    menu->add_item(setting_builder(
          "Snake color: ", 
          std::make_unique<ui::ColorValuePresenter>(config_id::SNAKE_COLOR, std::make_unique<xlib::X11_ColorLabel>(snake_color, geometry::Rectangle{.width = 100U, .height = items_height }, value_color_scheme)),
          key_color_scheme));
    menu->add_item(setting_builder(
          "Snake size: ", 
          std::make_unique<abstractions::ui::RestrictedValuePresenter<decltype(snake_size)>>(config_id::SNAKE_SIZE, std::make_unique<xlib::X11_TextLabel>(std::to_string(snake_size), geometry::Rectangle{}, value_color_scheme)),
          key_color_scheme));
    menu->add_item(setting_builder(
          "Food color: ", 
          std::make_unique<ui::ColorValuePresenter>(config_id::FOOD_COLOR, std::make_unique<xlib::X11_ColorLabel>(food_color, geometry::Rectangle{.width = 100U, .height = items_height }, value_color_scheme)),
          key_color_scheme));
  }

  void GameSettings::activate() {
    update();
  }

  void GameSettings::handle_key_press(const KeySym& key_sym, const unsigned int& mask) {
    switch(key_sym) {
      case XK_Escape: helpers::Helper::SendChangeViewEvent(views::ViewID::MENU); break;
      case XK_Down: menu->move_to_next_item(); break;
      case XK_Up: menu->move_to_prev_item(); break;
      case XK_equal: if(!(mask & ShiftMask)) break;
      case XK_Right:
      case XK_KP_Add: current_item_as_setting(*menu)->increase(); break;
      case XK_minus: if(mask != 0u) break;
      case XK_Left:
      case XK_KP_Subtract: current_item_as_setting(*menu)->decrease(); break;
    }

    update();
  }

  void GameSettings::update() {
    ui::CenterWindowAnchorHandler anchor_handler(menu.get());
    menu->get_current_item()->get()->set_focused(true);
    menu->show(true);
  }

  GameSettings::Setting* GameSettings::current_item_as_setting(const abstractions::ui::Menu& menu) {
    return static_cast<GameSettings::Setting*>(menu.get_current_item()->get());
  }
}
