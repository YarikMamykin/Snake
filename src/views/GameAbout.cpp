#include "GameAbout.hpp"
#include "WindowAnchorHandler.hpp"
#include "Helper.hpp"

namespace {
  const std::string about = "Classic 'Snake' game designed by Yaroslav Mamykin. Enjoy!";
  color::COLOR_SCHEME_TYPE text_label_color_scheme = {
    { color::ColorSchemeID::BackgroundColor, 0UL },
    { color::ColorSchemeID::TextColor, (255UL << 8) },
    { color::ColorSchemeID::FrameColor, (255UL << 16) }
  };
}

namespace views {

  GameAbout::GameAbout(xlib::X11_Window* x_window) 
  : x_window(x_window)
  , text_label(about, {}, text_label_color_scheme) {
  }
  
  void GameAbout::activate() {
    ui::WindowAnchorHandler<xlib::X11_TextLabel>(&text_label, x_window);
    text_label.show(true);
  }

  void GameAbout::deactivate() {
  }

  void GameAbout::handle_key_press(const KeySym&& key_sym, const unsigned int&& mask) {
    switch(key_sym) {
      case XK_Escape: helpers::Helper::SendChangeViewEvent(views::ViewID::MENU); 
    }
  }


}
