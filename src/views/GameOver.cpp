#include "GameOver.hpp"
#include "Helper.hpp"
#include "WindowAnchorHandler.hpp"

namespace {
  color::COLOR_SCHEME_TYPE color_scheme = {
    { color::ColorSchemeID::BackgroundColor, 0UL },
    { color::ColorSchemeID::FrameColor, ~0UL },
    { color::ColorSchemeID::TextColor, (255UL << 16) }
  };
}

namespace views {

  GameOver::GameOver(xlib::X11_Window* x_window) 
  : x_window(x_window) 
  , colorized_text_label(new xlib::X11_ColorizedTextLabel("GAME OVER", {}, color_scheme, color::ColorPallete({
        color::Color("#ff0000"),
        color::Color("#00ff00"),
        color::Color("#0000ff"),
        color::Color("#ffff00"),
        color::Color("#00ffff"),
        color::Color("#ff00ff"),
        }), x_window)) 
  , timer(std::chrono::milliseconds(130u)) {
    auto colorized_text_label_ptr = colorized_text_label.get();
    timer.callback = [colorized_text_label_ptr, x_window]() {
      colorized_text_label_ptr->shift_colors();
      colorized_text_label_ptr->show(true);
      XFlush(x_window->x_display.display); 
    };
  }

  GameOver::~GameOver() {
    timer.stop();
  }

  void GameOver::activate() {
    ui::WindowAnchorHandler<xlib::X11_ColorizedTextLabel>(colorized_text_label.get(), x_window);
    timer.launch();
    colorized_text_label->show(true);
  }

  void GameOver::deactivate() { }

  void GameOver::handle_key_press(const KeySym&& key_sym, const unsigned int&& mask) {
    switch(key_sym) {
      case XK_Escape: 
        {
          helpers::Helper::SendChangeViewEvent(x_window, views::ViewID::MENU);
          break;
        }
    }
  }
}
