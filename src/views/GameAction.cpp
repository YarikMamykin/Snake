#include "GameAction.hpp"
#include "Helper.hpp"
#include "Settings.hpp"
#include <iostream>
#include <thread>
#include "ColorPallete.hpp"

namespace views {

  GameAction::GameAction(xlib::X11_Window* x_window) 
  : x_window(x_window) 
  , snake(x_window, 
      configuration::Settings::get_concrete<color::ColorPallete>(configuration::ConfigID::SNAKE_COLOR).get_current_color(), 
      geometry::Rectangle { .x = configuration::Settings::get_concrete<int>(configuration::ConfigID::SNAKE_HEAD_X),
                            .y = configuration::Settings::get_concrete<int>(configuration::ConfigID::SNAKE_HEAD_Y),
                            .width = configuration::Settings::get_concrete<unsigned int>(configuration::ConfigID::SNAKE_HEAD_WIDTH),
                            .height = configuration::Settings::get_concrete<unsigned int>(configuration::ConfigID::SNAKE_HEAD_HEIGHT)}) 
  , snake_direction(game_objects::SnakeDirection::Right) {
    auto snake_timeout_ptr = configuration::Settings::get_concrete_ptr<std::chrono::milliseconds>(configuration::ConfigID::SNAKE_TIMEOUT);
    auto snake_speed_ptr = configuration::Settings::get_concrete_ptr<configuration::SNAKE_SPEED_TYPE>(configuration::ConfigID::SNAKE_SPEED);

    std::chrono::milliseconds snake_speed_in_time(1ul + snake_speed_ptr->get_value().get_max() - snake_speed_ptr->get_value().get_restricted_value());
    timer.timeout = std::chrono::milliseconds(snake_speed_in_time.count() * snake_timeout_ptr->get_value().count());
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
    timer.launch();
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
      case XK_j:
      case XK_Down: 
        {
          this->snake_direction = game_objects::SnakeDirection::Down;
          break;
        }
      case XK_k:
      case XK_Up: 
        {
          this->snake_direction = game_objects::SnakeDirection::Up;
          break;
        }
      case XK_l:
      case XK_Right: 
        {
          this->snake_direction = game_objects::SnakeDirection::Right;
          break;
        }
      case XK_h:
      case XK_Left: 
        {
          this->snake_direction = game_objects::SnakeDirection::Left;
          break;
        }
    }
  }
}
