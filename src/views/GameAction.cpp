#include "GameAction.hpp"
#include "Helper.hpp"
#include "Settings.hpp"
#include <iostream>
#include <thread>
#include "ColorPallete.hpp"
#include "XlibWrapper.hpp"

namespace views {

  GameAction::GameAction(xlib::X11_Window* x_window) 
  : x_window(x_window) 
  , snake(x_window, 
      configuration::Settings::get_concrete<color::ColorPallete>(configuration::ConfigID::SNAKE_COLOR).get_current_color(), 
      geometry::Rectangle { .x = 10u, .y = 10u,
                            .width = configuration::Settings::get_concrete<configuration::RESTRICTED_UINT>(configuration::ConfigID::SNAKE_HEAD_WIDTH).get_restricted_value(),
                            .height = configuration::Settings::get_concrete<configuration::RESTRICTED_UINT>(configuration::ConfigID::SNAKE_HEAD_HEIGHT).get_restricted_value()}) 
  , mcontroller(snake, x_window)
  , snake_direction(game_objects::SnakeDirection::Right) 
  , paused(false) {
    auto snake_timeout_ptr = configuration::Settings::get_concrete_ptr<std::chrono::milliseconds>(configuration::ConfigID::SNAKE_TIMEOUT);
    auto snake_speed_ptr = configuration::Settings::get_concrete_ptr<configuration::RESTRICTED_ULONG>(configuration::ConfigID::SNAKE_SPEED);

    std::chrono::milliseconds snake_speed_in_time(snake_speed_ptr->get_value().get_min() + snake_speed_ptr->get_value().get_max() - snake_speed_ptr->get_value().get_restricted_value());
    snake_timer.timeout = std::chrono::milliseconds(snake_speed_in_time.count() * snake_timeout_ptr->get_value().count());
    snake_timer.callback = [this, x_window]() { 
      this->snake.move(this->snake_direction); 
    };

    mcontroller.set_current_food(food_generator.generate(x_window));
    movement_controller_timer.timeout = snake_timer.timeout;
    movement_controller_timer.callback = [this, x_window]() {
      if(!mcontroller.validate()) {
        this->deactivate();
      }
      if(mcontroller.food_eaten()) {
        mcontroller.set_current_food(food_generator.generate(x_window));
        mcontroller.increase_snake();
      }
      // We need to redraw food periodically 
      // because in other case only Snake is visible.
      // Behavior caused with regular XFlush calls, needed for proper render.
      mcontroller.get_current_food().show();
    };
  }

  GameAction::~GameAction() {
    snake_timer.stop();
    movement_controller_timer.stop();
  }

  void GameAction::activate() {
    if(!paused) {
      snake_timer.launch();
      movement_controller_timer.launch();
    }
  }

  void GameAction::deactivate() {
    helpers::Helper::SendChangeViewEvent(x_window, views::ViewID::OVER);
    xlib::XlibWrapper::self()->flush_buffer();
  }

  void GameAction::set_paused(const bool pause_flag) {
    paused = pause_flag;

    if(pause_flag) {
      snake_timer.stop();
      // TODO: draw_pause screen or whatever
      return;
    }

    if(!pause_flag) {
      // TODO: redraw background
      snake_timer.launch();
    }
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
      case XK_space:
        {
          set_paused(!paused);
          break;
        }
    }
  }
}
