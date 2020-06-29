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

}
