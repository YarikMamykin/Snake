#include "GameOver.hpp"
#include "Helper.hpp"

namespace views {

  GameOver::GameOver(xlib::X11_Window* x_window) 
  : x_window(x_window) 
  , text("G A M E   O V E R") {
  }

  void GameOver::activate() {
    const auto&& window_frame = x_window->get_frame();
    const int&& font_height = x_window->font_info->ascent + x_window->font_info->descent;
    const int text_width = XTextWidth(x_window->font_info, this->text.c_str(), this->text.length());
    const int text_x_coord = window_frame.width/2 - text_width/2; 
    const int text_y_coord = window_frame.height/2 - (font_height)/2; 
    const auto& window_color_scheme = x_window->get_color_scheme();

    XSetForeground(x_window->x_display.display, 
        x_window->graphical_context, 
        window_color_scheme.at(color::ColorSchemeID::FontColor).to_long());

    XDrawString(x_window->x_display.display, 
        x_window->window, 
        x_window->graphical_context, 
        text_x_coord,
        text_y_coord,
        this->text.c_str(), 
        this->text.length());
  }

  void GameOver::deactivate() {
  }

  void GameOver::handle_key_press(const KeySym&& key_sym, const unsigned int&& mask) {
    switch(key_sym) {
      case XK_Escape: {
                        helpers::Helper::SendChangeViewEvent(x_window, views::ViewID::MENU);
                        break;
                      }
    }
  }
}
