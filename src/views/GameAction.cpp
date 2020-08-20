#include "GameAction.hpp"

namespace views {

  GameAction::GameAction(xlib::X11_Window* x_window) :
  x_window(x_window) {
  }

  GameAction::~GameAction() {
  }

  void GameAction::activate() {

  }

  void GameAction::deactivate() {
  }

  void GameAction::handle_key_press(const KeySym&& key_sym) {
    switch(key_sym) {
      case XK_Down:
        {
        }
      case XK_Up:
        {
        }   
      case XK_Return:
        {
        }
    }
  }
}
