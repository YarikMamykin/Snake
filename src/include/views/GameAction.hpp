#ifndef SRC_INCLUDE_VIEWS_GAMEACTION_HPP
#define SRC_INCLUDE_VIEWS_GAMEACTION_HPP

#include "View.hpp"
#include "X11_Window.hpp"

namespace views {

  class GameAction : public View {
    public:
      explicit GameAction(xlib::X11_Window* x_window);
      virtual ~GameAction();

    public:
      virtual void activate() override;
      virtual void deactivate() override;

    private:
      xlib::X11_Window* x_window;
  };

}
#endif /* SRC_INCLUDE_VIEWS_GAMEACTION_HPP */
