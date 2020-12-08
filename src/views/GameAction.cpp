#include "GameAction.hpp"
#include "Helper.hpp"
#include <iostream>
#include <thread>

namespace views {

  GameAction::GameAction(xlib::X11_Window* x_window) 
  : x_window(x_window) 
  , snake(x_window) 
  , snake_direction(game_objects::SnakeDirection::Right) {
    timer.timeout = std::chrono::milliseconds(50);
    timer.callback = [this]() {
      this->snake.move(this->snake_direction);
    };
  }

  GameAction::~GameAction() {
    timer.stop();
  }

  void GameAction::activate() {
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
      case XK_Down: 
        {
          this->snake_direction = game_objects::SnakeDirection::Down;
          break;
        }
      case XK_Up: 
        {
          this->snake_direction = game_objects::SnakeDirection::Up;
          break;
        }
      case XK_Right: 
        {
          this->snake_direction = game_objects::SnakeDirection::Right;
          break;
        }
      case XK_Left: 
        {
          this->snake_direction = game_objects::SnakeDirection::Left;
          break;
        }
    }
  }
}
