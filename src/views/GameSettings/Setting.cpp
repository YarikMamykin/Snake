#include "Setting.hpp"
#include <abstractions/ui/Object.hpp>
#include <abstractions/ui/TextLabel.hpp>

namespace {
  color::COLOR_SCHEME_TYPE menu_color_scheme = {
    { color::ColorSchemeID::BackgroundColor, 0UL },
    { color::ColorSchemeID::FrameColor, ~0UL }
  };
}


namespace views {

  Setting::Setting(std::unique_ptr<abstractions::ui::TextLabel> key_presenter, 
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

  void Setting::increase() {
    increase_binder();
  }

  void Setting::decrease() {
    decrease_binder();
  }

}

