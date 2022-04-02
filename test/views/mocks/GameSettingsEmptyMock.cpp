#include "gmock/gmock.h"
#include "views/GameSettings/GameSettings.hpp"

namespace color {
  Color::Color(const unsigned long&) {}
}

namespace {
  color::COLOR_SCHEME_TYPE menu_color_scheme = {
    { color::ColorSchemeID::BackgroundColor, 0UL },
    { color::ColorSchemeID::FrameColor, ~0UL }
  };
}

namespace xlib {
	X11_Menu::X11_Menu(const ::ui::LayoutType& layout, 
               const geometry::Rectangle& frame, 
               const color::COLOR_SCHEME_TYPE& color_scheme, 
               const unsigned int& spacing) 
    : abstractions::ui::Menu(layout, frame, color_scheme, spacing) { }
	X11_Menu::~X11_Menu() = default;
	
	void X11_Menu::show(bool) {} 
	void X11_Menu::show_frame(bool) {}

}

namespace views {
	GameSettings::Setting::Setting(
			std::unique_ptr<abstractions::ui::TextLabel> key_presenter, 
			std::unique_ptr<abstractions::ui::Object> value_presenter,
			std::function<void()> increase_binder, 
			std::function<void()> decrease_binder) 
  : xlib::X11_Menu(::ui::LayoutType::HORIZONTAL, {}, menu_color_scheme, 30U) {} 

  void GameSettings::Setting::increase() { }

  void GameSettings::Setting::decrease() { }
}

namespace views {
  GameSettings::GameSettings() : menu(new xlib::X11_Menu(ui::LayoutType::VERTICAL, {}, color::COLOR_SCHEME_TYPE(), 20U)) {} 
  void GameSettings::activate() {} 
  void GameSettings::handle_key_press(const KeySym& key_sym, const unsigned int& mask) {}

  void GameSettings::update() {}
  GameSettings::Setting* GameSettings::current_item_as_setting(const abstractions::ui::Menu& menu) {return nullptr;}
}

