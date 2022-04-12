#include "GameOver.hpp"
#include "anchor_handlers/CenterWindowAnchorHandler.hpp"
#include "configuration/Settings.hpp"
#include "commands/ChangeView/ChangeView.hpp"

namespace {
  color::COLOR_SCHEME_TYPE color_scheme = {
    { color::ColorSchemeID::BackgroundColor, 0UL },
    { color::ColorSchemeID::FrameColor, ~0UL },
    { color::ColorSchemeID::TextColor, (255UL << 16) }
  };
}

namespace views {

  GameOver::GameOver() 
  : colorized_text_label(new xlib::X11_ColorizedTextLabel(
        "GAME OVER", {}, color_scheme, 
        color::ColorPallete(std::list<color::Color>{
          color::Color("#ff0000"),
          color::Color("#00ff00"),
          color::Color("#0000ff"),
          color::Color("#ffff00"),
          color::Color("#00ffff"),
          color::Color("#ff00ff"),
        }))) 
  , timer(
      config::get_concrete<std::chrono::milliseconds>(config_id::GAME_OVER_TIMEOUT),
      [colorized_text_label_ptr = this->colorized_text_label.get()]() {
        colorized_text_label_ptr->shift_colors();
        colorized_text_label_ptr->show(true);
      }) { }

  GameOver::~GameOver() = default;

  void GameOver::activate() {
    ui::CenterWindowAnchorHandler(colorized_text_label.get());
    timer.launch();
  }

  void GameOver::handle_key_press(const KeySym& key_sym, const unsigned int& mask) {
    switch(key_sym) {
      case XK_Escape: 
        {
          commands::Command::push_xlib_command(std::make_unique<commands::ChangeView>(views::ViewID::MENU));
        }
    }
  }
}
