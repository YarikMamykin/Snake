#ifndef SRC_INCLUDE_VIEWS_GAMEACTION_HPP
#define SRC_INCLUDE_VIEWS_GAMEACTION_HPP

#include "View.hpp"
#include "KeyPressHandler.hpp"
#include "X11_TextLabel.hpp"
#include "Timer.hpp"
#include "Snake.hpp"
#include "Constants.hpp"
#include "FoodGenerator.hpp"
#include "MovementController.hpp"
#include <memory>

namespace views {

  class GameAction final : public View, 
                           public events::KeyPressHandler {
    public:
      explicit GameAction();
      ~GameAction();

    public:
      virtual void activate() override;
      virtual void handle_key_press(const KeySym& key_sym, const unsigned int& mask) override;

    private:
      void set_paused(const bool pause_flag);
      void deactivate();

    private:
      std::unique_ptr<game_objects::Snake> snake;
      std::unique_ptr<game_objects::MovementController> mcontroller;
      timing::Timer action_timer;
      timing::Timer movement_controller_timer;
      std::unique_ptr<game_objects::FoodGenerator> food_generator;
      bool paused;
      game_objects::SnakeDirection snake_direction;
      xlib::X11_TextLabel score_counter_label;
  };

}
#endif /* SRC_INCLUDE_VIEWS_GAMEACTION_HPP */
