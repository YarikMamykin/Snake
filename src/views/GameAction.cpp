#include "views/GameAction.hpp"
#include "configuration/Settings.hpp"
#include "color/ColorPallete.hpp"
#include "commands/ChangeView.hpp"
#include "game_objects/Snake.hpp"
#include "game_objects/FoodGenerator.hpp"
#include "game_objects/MovementController.hpp"
#include "game_objects/Info.hpp"
#include "timing/Timer.hpp"
#include "abstractions/values/RestrictedValue.hpp"

namespace {
  std::chrono::milliseconds time_count {0u};
  constexpr std::chrono::milliseconds time_count_step {25u};
  unsigned long int score_count {0ul};
}

namespace views {

  using ConfigID = configuration::ConfigID;
  using Sets = configuration::Settings;
  using RESTRICTED_UINT = abstractions::values::RestrictedValue<unsigned int>;
  using RESTRICTED_ULONG = abstractions::values::RestrictedValue<unsigned long>;

  GameAction::GameAction() 
  : snake_direction(game_objects::SnakeDirection::Right) 
  , paused(false) {

    // snake params from settings
    auto&& snake_color = Sets::get_concrete<color::ColorPallete>(ConfigID::SNAKE_COLOR).get_current_color();
    auto&& snake_head_width = Sets::get_concrete<RESTRICTED_UINT>(ConfigID::SNAKE_SIZE).get_restricted_value() * Sets::get_concrete<const unsigned int>(ConfigID::SIZE_MULTIPLIER);
    auto&& snake_head_height = Sets::get_concrete<RESTRICTED_UINT>(ConfigID::SNAKE_SIZE).get_restricted_value() * Sets::get_concrete<const unsigned int>(ConfigID::SIZE_MULTIPLIER) / 2u;
    auto&& snake_timeout = Sets::get_concrete_ref<std::chrono::milliseconds>(ConfigID::SNAKE_TIMEOUT);
    auto&& snake_speed = Sets::get_concrete_ref<RESTRICTED_ULONG>(ConfigID::SNAKE_SPEED);
    auto&& snake_speed_multiplier = Sets::get_concrete_ref<std::chrono::milliseconds>(ConfigID::SNAKE_SPEED_MULTIPLIER);

    // windows frame from settings
    const auto& win_frame = config::get_concrete_ref<geometry::Rectangle>(config_id::WINDOW_FRAME);

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
        ++score_count;
      }
      time_count += time_count_step;
      info->update(score_count, time_count);
    };

    action_timer = std::make_unique<timing::Timer>(action_timer_timeout, action_timer_callback);
    snake = std::make_unique<game_objects::Snake>(snake_color, geometry::Rectangle { .x = 1, .y = 1, .width = snake_head_width, .height = snake_head_height});
    mcontroller = std::make_unique<game_objects::MovementController>(*snake.get(), win_frame.width, win_frame.height);
    food_generator = std::make_unique<game_objects::FoodGenerator>(win_frame.width, win_frame.height);
    info = std::make_unique<game_objects::Info>();
  }

  GameAction::~GameAction() = default;

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
