#include "Item.hpp"

namespace {
  color::COLOR_SCHEME_TYPE text_labels_color_scheme = {
    { color::ColorSchemeID::BackgroundColor, 0UL },
    { color::ColorSchemeID::TextColor, (255UL << 8) },
    { color::ColorSchemeID::FrameColor, (255UL << 16) }
  };
}

namespace views {

  Item::Item(
      const std::string& name, 
      std::function<void()> activation_callback)
  : xlib::X11_TextLabel(name, {}, text_labels_color_scheme)
  , activation_callback(activation_callback) { }

  void Item::activate() {
    if(this->focused()) {
      this->activation_callback();
    }
  }

}
