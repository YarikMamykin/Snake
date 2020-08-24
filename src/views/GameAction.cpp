#include "GameAction.hpp"
#include "Helper.hpp"
#include "Constants.hpp"
#include <iostream>
#include <thread>

namespace views {

  GameAction::GameAction(xlib::X11_Window* x_window) 
  : x_window(x_window) 
  , snake(x_window) {
    timer.timeout = std::chrono::milliseconds(50);
    timer.callback = [this]() {
      std::cout << "AMMA WORKING!" << std::endl;
      this->snake.move(game_objects::SnakeDirection::Right);
    };
  }

  GameAction::~GameAction() {
    timer.stop();
    XFlush(x_window->x_display.display);
  }

  void GameAction::activate() {
    std::cout << std::boolalpha << "TIMER RUNNING " << timer.running() << std::endl;
    if(!timer.running()) {
      timer.launch();
    }
  }

  void GameAction::deactivate() {
  }

  void GameAction::handle_key_press(const KeySym&& key_sym) {
    switch(key_sym) {
      case XK_Escape:
        {
          auto event = helpers::Helper::ConstructChangeViewEvent(x_window, views::ViewID::MENU);
          XSendEvent(x_window->x_display.display, x_window->window, true, NoEventMask, &event);
          break;
        }
    }
  }
}
