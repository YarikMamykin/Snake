#include "gmock/gmock.h"
#include "views/GameMenu/GameMenu.hpp"
#include <xlib/X11_TextLabel/X11_TextLabel.hpp>

namespace xlib {
  X11_TextLabel::X11_TextLabel() = default;
  X11_TextLabel::X11_TextLabel(const std::string& text, 
      const geometry::Rectangle& frame, 
      const color::COLOR_SCHEME_TYPE& color_scheme){}
  X11_TextLabel::~X11_TextLabel() = default;

  void X11_TextLabel::show(bool) {}
  void X11_TextLabel::show_frame(bool) {}

  void X11_TextLabel::update() {}
  void X11_TextLabel::update_frame() {}
  const unsigned int X11_TextLabel::get_text_graphical_width() const{return 0u;}
  const unsigned int X11_TextLabel::get_text_graphical_height() const{return 0u;}
  void X11_TextLabel::hide_prev_frame(){}
}

namespace views {
  class Item {
  };
}

namespace views {
  GameMenu::GameMenu() = default;
  void GameMenu::activate() {}
  void GameMenu::handle_key_press(const KeySym& key_sym, const unsigned int& mask) {}

  void GameMenu::update() {}

  Item* GameMenu::current_item_as_game_menu_item(const abstractions::ui::Menu& menu) {
    return nullptr;
  }
}
