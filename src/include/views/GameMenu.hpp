#ifndef SRC_INCLUDE_VIEWS_GAMEMENU_HPP
#define SRC_INCLUDE_VIEWS_GAMEMENU_HPP

#include "View.hpp"
#include "X11_Window.hpp"
#include <list>

namespace views {

  class GameMenu : public View {
    private:
      struct Item {
        bool active;
        std::string name;
        XRectangle frame;
      };

    public:
      explicit GameMenu(xlib::X11_Window* x_window);
      virtual ~GameMenu();

    public:
      virtual void activate() override;
      virtual void deactivate() override;

      void add_item();

    private:
      xlib::X11_Window* x_window;
      bool active;
      std::list<Item> items;
  };
}

#endif /* SRC_INCLUDE_VIEWS_GAMEMENU_HPP */
