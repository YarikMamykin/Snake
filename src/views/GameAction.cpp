#include "GameAction.hpp"
#include "Settings.hpp"
#include "ColorPallete.hpp"
#include "ChangeView.hpp"
#include "Snake.hpp"
#include "FoodGenerator.hpp"
#include "MovementController.hpp"
#include "Timer.hpp"

namespace views {

  using namespace configuration;
  using Sets = configuration::Settings;

  GameAction::GameAction() 
  : snake_direction(game_objects::SnakeDirection::Right) 
  , paused(false) {

    // snake params from settings
    auto&& snake_color = Sets::get_concrete<color::ColorPallete>(ConfigID::SNAKE_COLOR).get_current_color();
    auto&& snake_head_width = Sets::get_concrete<RESTRICTED_UINT>(ConfigID::SNAKE_SIZE).get_restricted_value() * Sets::get_concrete<const unsigned int>(ConfigID::SIZE_MULTIPLIER);
    auto&& snake_head_height = Sets::get_concrete<RESTRICTED_UINT>(ConfigID::SNAKE_SIZE).get_restricted_value() * Sets::get_concrete<const unsigned int>(ConfigID::SIZE_MULTIPLIER) / 2u;
    auto&& snake_timeout = Sets::get_concrete_ptr<std::chrono::milliseconds>(ConfigID::SNAKE_TIMEOUT)->get_value();
    auto&& snake_speed = Sets::get_concrete_ptr<RESTRICTED_ULONG>(ConfigID::SNAKE_SPEED)->get_value();
    auto&& snake_speed_multiplier = Sets::get_concrete_ptr<std::chrono::milliseconds>(ConfigID::SNAKE_SPEED_MULTIPLIER)->get_value();

    // windows frame from settings
    const auto&& win_frame = configuration::Settings::get_concrete<geometry::Rectangle>(configuration::ConfigID::WINDOW_FRAME);

    // action_timer settings
    auto&& action_timer_timeout = (snake_speed.get_max() - snake_speed.get_restricted_value()) * snake_speed_multiplier + snake_timeout; 
    auto&& action_timer_callback = [this]() { 
      this->snake->move(this->snake_direction); 
      if(!mcontroller->validate()) {
        this->deactivate();
      }
      if(mcontroller->food_eaten()) {
        mcontroller->set_current_food(food_generator->generate());
        mcontroller->increase_snake();
      }
    };

    action_timer.reset(new timing::Timer(action_timer_timeout, action_timer_callback));
    snake.reset(new game_objects::Snake(snake_color, geometry::Rectangle { .x = 10u, .y = 100u, .width = snake_head_width, .height = snake_head_height}));
    mcontroller.reset(new game_objects::MovementController(*snake.get(), win_frame.width, win_frame.height));
    food_generator.reset(new game_objects::FoodGenerator(win_frame.width, win_frame.height));
  }

  GameAction::~GameAction() {
    action_timer->stop();
  }

  void GameAction::activate() {
    if(!paused) {
      mcontroller->set_current_food(food_generator->generate());
      action_timer->launch();
    }
  }

  void GameAction::deactivate() {
    commands::Command::push_xlib_command(new commands::ChangeView(views::ViewID::OVER));
  }

  void GameAction::set_paused(const bool pause_flag) {
    paused = pause_flag;

    if(pause_flag) {
      action_timer->stop();
      // TODO: draw_pause screen or whatever
      return;
    }

    if(!pause_flag) {
      // TODO: redraw background
      action_timer->launch();
    }
  }

  void GameAction::handle_key_press(const KeySym& key_sym, const unsigned int& mask) {
    switch(key_sym) {
      case XK_Down: 
        {
          this->snake_direction = game_objects::SnakeDirection::Down;
          return;
        }
      case XK_Up: 
        {
          this->snake_direction = game_objects::SnakeDirection::Up;
          return;
        }
      case XK_Right: 
        {
          this->snake_direction = game_objects::SnakeDirection::Right;
          return;
        }
      case XK_Left: 
        {
          this->snake_direction = game_objects::SnakeDirection::Left;
          return;
        }
      case XK_space:
        {
          set_paused(!paused);
          return;
        }
      case XK_Escape:
        {
          commands::Command::push_xlib_command(new commands::ChangeView(views::ViewID::MENU));
          return;
        }
    }
  }
}
