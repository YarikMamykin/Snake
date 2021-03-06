#include "GameOver.hpp"
#include "Helper.hpp"
#include "CenterWindowAnchorHandler.hpp"
#include "Settings.hpp"
#include "XlibWrapper.hpp"

namespace {
  color::COLOR_SCHEME_TYPE color_scheme = {
    { color::ColorSchemeID::BackgroundColor, 0UL },
    { color::ColorSchemeID::FrameColor, ~0UL },
    { color::ColorSchemeID::TextColor, (255UL << 16) }
  };
}

namespace views {

  GameOver::GameOver() 
  : colorized_text_label(new xlib::X11_ColorizedTextLabel("GAME OVER", {}, color_scheme, color::ColorPallete({
        color::Color("#ff0000"),
        color::Color("#00ff00"),
        color::Color("#0000ff"),
        color::Color("#ffff00"),
        color::Color("#00ffff"),
        color::Color("#ff00ff"),
        }))) 
  , timer(configuration::Settings::get_concrete<std::chrono::milliseconds>(configuration::ConfigID::GAME_OVER_TIMEOUT)) {
    auto colorized_text_label_ptr = colorized_text_label.get();
    timer.callback = [colorized_text_label_ptr]() {
      colorized_text_label_ptr->shift_colors();
      colorized_text_label_ptr->show(true);
      xlib::XlibWrapper::self()->flush_buffer();
    };
    ui::CenterWindowAnchorHandler(colorized_text_label.get());
  }

  GameOver::~GameOver() {
    timer.stop();
  }

  void GameOver::activate() {
    timer.launch();
    colorized_text_label->show(true);
  }

  void GameOver::handle_key_press(const KeySym&& key_sym, const unsigned int&& mask) {
    switch(key_sym) {
      case XK_Escape: 
        {
          helpers::Helper::SendChangeViewEvent(views::ViewID::MENU);
          break;
        }
    }
  }
}
