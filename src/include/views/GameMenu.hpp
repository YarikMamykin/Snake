#ifndef SRC_INCLUDE_VIEWS_GAMEMENU_HPP
#define SRC_INCLUDE_VIEWS_GAMEMENU_HPP

#include "View.hpp"
#include "UI_Object.hpp"
#include "X11_Window.hpp"
#include <list>

namespace views {

  class GameMenu final : public View, public ui::UI_Object {
    private:
      struct Item : public ui::UI_Object {
        bool active;
        std::string name;
        XRectangle frame;
        
        static const unsigned int left_text_margin;
        static const unsigned int top_text_margin;

        Item(xlib::X11_Window* x_window, 
             bool active, 
             const std::string& name, 
             const XRectangle& frame = {});
        ~Item();
        void show_text(xlib::X11_Window* x_window) const;
        void show_frame(xlib::X11_Window* x_window) const;
        void hide_frame(xlib::X11_Window* x_window) const;
        void show_focus(xlib::X11_Window* x_window) const;
        void hide_focus(xlib::X11_Window* x_window) const;
        void show(xlib::X11_Window* x_window) const;

        int get_width(xlib::X11_Window* x_window) const;
        int get_height(xlib::X11_Window* x_window) const;

        virtual void on_event(const XEvent& event) override; 
      };

    public:
      explicit GameMenu(xlib::X11_Window* x_window);
      ~GameMenu();

    public:
      virtual void activate() override;
      virtual void deactivate() override;
      virtual void on_event(const XEvent& event) override; 

    private:
      xlib::X11_Window* x_window;
      std::list<Item> items;
  };
}

#endif /* SRC_INCLUDE_VIEWS_GAMEMENU_HPP */
