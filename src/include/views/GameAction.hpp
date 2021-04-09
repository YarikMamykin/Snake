#ifndef SRC_INCLUDE_VIEWS_GAMEACTION_HPP
#define SRC_INCLUDE_VIEWS_GAMEACTION_HPP
#include "abstractions/views/View.hpp"
#include "abstractions/event_handling/KeyPressHandler.hpp"
#include "constants/Constants.hpp"
#include <memory>

namespace game_objects {
  class Snake;
  class FoodGenerator;
  class MovementController;
}

namespace timing {
  struct Timer;
}

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
      std::unique_ptr<game_objects::FoodGenerator> food_generator;
      std::unique_ptr<timing::Timer> action_timer;
      bool paused;
      game_objects::SnakeDirection snake_direction;
  };

}

#endif /* SRC_INCLUDE_VIEWS_GAMEACTION_HPP */
