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
        const unsigned int left_text_margin;
        const unsigned int top_text_margin;

        Item(bool active, const std::string& name, const XRectangle& frame = {});
        void show_text(xlib::X11_Window* x_window);
        void show_frame(xlib::X11_Window* x_window);
        void show(xlib::X11_Window* x_window);

        int get_width(xlib::X11_Window* x_window) const;
        int get_height(xlib::X11_Window* x_window) const;
      };

    public:
      explicit GameMenu(xlib::X11_Window* x_window);
      virtual ~GameMenu();

    public:
      virtual void activate() override;
      virtual void deactivate() override;

    private:
      xlib::X11_Window* x_window;
      std::list<Item> items;
  };
}

#endif /* SRC_INCLUDE_VIEWS_GAMEMENU_HPP */
