#ifndef SRC_INCLUDE_VIEWS_GAMEACTION_HPP
#define SRC_INCLUDE_VIEWS_GAMEACTION_HPP

#include "View.hpp"
#include "KeyPressHandler.hpp"
#include "X11_Window.hpp"
#include "Timer.hpp"
#include "Snake.hpp"

namespace views {

  class GameAction : public View, public events::KeyPressHandler {
    public:
      explicit GameAction(xlib::X11_Window* x_window);
      ~GameAction();

    public:
      virtual void activate() override;
      virtual void deactivate() override;
      virtual void handle_key_press(const KeySym&& key_sym) override;

    public:
      game_objects::Snake snake;
    private:
      xlib::X11_Window* x_window;
      timing::Timer timer;

  };

}
#endif /* SRC_INCLUDE_VIEWS_GAMEACTION_HPP */
