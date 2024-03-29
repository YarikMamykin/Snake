#include "GameAbout.hpp"
#include "anchor_handlers/CenterWindowAnchorHandler.hpp"
#include <xlib/X11_TextLabel/X11_TextLabel.hpp>
#include <commands/ChangeView/ChangeView.hpp>

namespace {
  const std::string about = "Classic 'Snake' game designed by Yaroslav Mamykin. Enjoy!";
  color::COLOR_SCHEME_TYPE text_label_color_scheme = {
    { color::ColorSchemeID::BackgroundColor, 0UL },
    { color::ColorSchemeID::TextColor, (255UL << 8) },
    { color::ColorSchemeID::FrameColor, (255UL << 16) }
  };

  std::unique_ptr<abstractions::ui::TextLabel>
    define_label(abstractions::ui::TextLabel* tlabel) {
      if(tlabel) {
        return std::unique_ptr<abstractions::ui::TextLabel>(tlabel);
      }

      return std::unique_ptr<abstractions::ui::TextLabel>(new xlib::X11_TextLabel(about, {}, text_label_color_scheme));
    }
}

namespace views {

  GameAbout::GameAbout(TextLabel* tlabel) 
  : text_label(define_label(tlabel)) { }
  
  void GameAbout::activate() {
    ui::CenterWindowAnchorHandler(text_label.get());
    text_label->show(true);
  }

  void GameAbout::handle_key_press(const KeySym& key_sym, const unsigned int& mask) {
    switch(key_sym) {
      case XK_Escape: commands::Command::push_xlib_command(std::make_unique<commands::ChangeView>(views::ViewID::MENU));
    }
  }


}
