#include "GameAction.hpp"
#include "Helper.hpp"
#include "Settings.hpp"
#include <iostream>
#include <thread>
#include "ColorPallete.hpp"

namespace views {

  GameAction::GameAction(xlib::X11_Window* x_window) 
  : x_window(x_window) 
  , snake(x_window, configuration::Settings::get_concrete<color::ColorPallete>(configuration::ConfigID::SNAKE_COLOR).get_current_color()) 
  , snake_direction(game_objects::SnakeDirection::Right) {
    timer.timeout = configuration::Settings::get_concrete<std::chrono::milliseconds>(configuration::ConfigID::SNAKE_TIMEOUT);
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
    helpers::Helper::SendChangeViewEvent(x_window, views::ViewID::OVER);
    XFlush(x_window->x_display.display); // Necessary in case of multithreading!
  }

  void GameAction::handle_key_press(const KeySym&& key_sym, const unsigned int&& mask) {
    switch(key_sym) {
      case XK_Escape:
        {
          helpers::Helper::SendChangeViewEvent(x_window, views::ViewID::MENU);
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
