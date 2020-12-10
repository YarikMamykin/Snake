#include "GameAction.hpp"
#include "Helper.hpp"
#include <iostream>
#include <thread>

namespace views {

  GameAction::GameAction(xlib::X11_Window* x_window) 
  : x_window(x_window) 
  , snake(x_window) 
  , snake_direction(game_objects::SnakeDirection::Right) {
    timer.timeout = std::chrono::milliseconds(120);
    timer.callback = [this, x_window]() {
      try { 
        this->snake.move(this->snake_direction); 
      }
      catch(...) { 
        this->deactivate();
      }
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
    this->timer.stop_async(); 
    auto event = helpers::Helper::ConstructChangeViewEvent(x_window, views::ViewID::OVER);
    XSendEvent(x_window->x_display.display, x_window->window, true, NoEventMask, &event);
    XFlush(x_window->x_display.display); // Necessary in case of multithreading!
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

  const int GameAction::get_event_handling_mask() const {
    return events::KeyPressHandler::mask;
  }
}
