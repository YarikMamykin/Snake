#include "GameAction.hpp"
#include "Helper.hpp"
#include "Settings.hpp"
#include <iostream>
#include <thread>
#include "ColorPallete.hpp"
#include "XlibWrapper.hpp"
#include "X11_TextLabel.hpp"

namespace {
  color::COLOR_SCHEME_TYPE score_counter_label_color_scheme = {
    { color::ColorSchemeID::BackgroundColor, 0UL },
    { color::ColorSchemeID::FrameColor, "#ff0000" },
    { color::ColorSchemeID::TextColor, "#00ffff"}
  };
}

namespace views {

  using namespace configuration;
  using Sets = configuration::Settings;

  GameAction::GameAction() 
  : snake_direction(game_objects::SnakeDirection::Right) 
  , paused(false) 
  , score_counter_label(std::to_string(1u), geometry::Rectangle{}, score_counter_label_color_scheme) {
    auto&& win_attr = xlib::XlibWrapper::self()->get_window_attributes();
    auto&& snake_color = Sets::get_concrete<color::ColorPallete>(ConfigID::SNAKE_COLOR).get_current_color();
    auto&& snake_head_width = Sets::get_concrete<RESTRICTED_UINT>(ConfigID::SNAKE_SIZE).get_restricted_value() * Sets::get_concrete<const unsigned int>(ConfigID::SIZE_MULTIPLIER);
    auto&& snake_head_height = Sets::get_concrete<RESTRICTED_UINT>(ConfigID::SNAKE_SIZE).get_restricted_value() * Sets::get_concrete<const unsigned int>(ConfigID::SIZE_MULTIPLIER) / 2u;

    snake.reset(new game_objects::Snake(snake_color, geometry::Rectangle { .x = 10u, .y = 100u, .width = snake_head_width, .height = snake_head_height}));
    mcontroller.reset(new game_objects::MovementController(*snake.get(), win_attr.width, win_attr.height));
    food_generator.reset(new game_objects::FoodGenerator(win_attr.width, win_attr.height));

    geometry::Point&& window_bottom_center{win_attr.width/2u, win_attr.height};
    score_counter_label.set_center(window_bottom_center.x, window_bottom_center.y - score_counter_label.get_height()/2u);

    auto snake_timeout_ptr = Sets::get_concrete_ptr<std::chrono::milliseconds>(ConfigID::SNAKE_TIMEOUT);
    auto snake_speed_ptr = Sets::get_concrete_ptr<RESTRICTED_ULONG>(ConfigID::SNAKE_SPEED);

    std::chrono::milliseconds snake_speed_in_time(snake_speed_ptr->get_value().get_max() - snake_speed_ptr->get_value().get_restricted_value());
    action_timer.timeout = std::chrono::milliseconds(snake_speed_in_time.count() * std::chrono::milliseconds(10u).count() +  snake_timeout_ptr->get_value().count());
    action_timer.callback = [this]() { 
      this->snake->move(this->snake_direction); 
      if(!mcontroller->validate()) {
        this->deactivate();
      }
      if(mcontroller->food_eaten()) {
        mcontroller->set_current_food(food_generator->generate());
        mcontroller->increase_snake();
      }
      if(!snake->head_frame().do_not_cross(score_counter_label.get_frame())) {
        auto&& current_snake_size = snake->size();
        for(unsigned int i = 0u; i < current_snake_size; ++i) {
          mcontroller->increase_snake();
        }
      }
      // We need to redraw food periodically 
      // because in other case only Snake is visible.
      // Behavior caused with regular XFlush calls, needed for proper render.
      mcontroller->get_current_food().show();
      score_counter_label.show(false);
      score_counter_label.show_frame(false);
      score_counter_label.set_text(std::to_string(snake->size()));
      score_counter_label.show(true);
      score_counter_label.show_frame(true);
    };

    mcontroller->set_current_food(food_generator->generate());
  }

  GameAction::~GameAction() {
    action_timer.stop();
  }

  void GameAction::activate() {
    if(!paused) {
      action_timer.launch();
    }
  }

  void GameAction::deactivate() {
    helpers::Helper::SendChangeViewEvent(views::ViewID::OVER);
    xlib::XlibWrapper::self()->flush_buffer();
  }

  void GameAction::set_paused(const bool pause_flag) {
    paused = pause_flag;

    if(pause_flag) {
      action_timer.stop();
      // TODO: draw_pause screen or whatever
      return;
    }

    if(!pause_flag) {
      // TODO: redraw background
      action_timer.launch();
    }
  }

  void GameAction::handle_key_press(const KeySym&& key_sym, const unsigned int&& mask) {
    switch(key_sym) {
      case XK_Escape:
        {
          helpers::Helper::SendChangeViewEvent(views::ViewID::MENU);
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
