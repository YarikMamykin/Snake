#ifndef SRC_INCLUDE_VIEWS_GAMEACTION_HPP
#define SRC_INCLUDE_VIEWS_GAMEACTION_HPP

#include "View.hpp"
#include "KeyPressHandler.hpp"
#include "X11_Window.hpp"
#include "Timer.hpp"
#include "Snake.hpp"
#include "Constants.hpp"

namespace views {

  class GameAction final : public View, 
                           public events::KeyPressHandler {
    public:
      explicit GameAction(xlib::X11_Window* x_window);
      ~GameAction();

    public:
      virtual void activate() override;
      virtual void deactivate() override;
      virtual void handle_key_press(const KeySym&& key_sym, const unsigned int&& mask) override;

    private:
      void set_paused(const bool pause_flag);

    public:
      game_objects::Snake snake;
    private:
      xlib::X11_Window* x_window;
      timing::Timer snake_timer;
      bool paused;
      game_objects::SnakeDirection snake_direction;
  };

}
#endif /* SRC_INCLUDE_VIEWS_GAMEACTION_HPP */
