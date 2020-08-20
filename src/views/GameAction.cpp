#include "GameAction.hpp"
#include "Helper.hpp"
#include "Constants.hpp"

namespace views {

  GameAction::GameAction(xlib::X11_Window* x_window) :
  x_window(x_window) {
    x_window->redraw_background();
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
          break;
        }
      case XK_Up:
        {
          break;
        }   
      case XK_Return:
        {
          break;
        }
      case XK_Escape:
        {
          auto event = helpers::Helper::ConstructChangeViewEvent(x_window, views::ViewID::MENU);
          XSendEvent(x_window->x_display.display, x_window->window, true, NoEventMask, &event);
          break;
        }
    }
  }
}
