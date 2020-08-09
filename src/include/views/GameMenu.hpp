#ifndef SRC_INCLUDE_VIEWS_GAMEMENU_HPP
#define SRC_INCLUDE_VIEWS_GAMEMENU_HPP

#include "View.hpp"
#include "UI_Object.hpp"
#include "X11_Window.hpp"
#include <list>

namespace views {

  class GameMenu final : public View, public ui::MouseMotionHandler {
    private:
      struct Item : public ui::MouseMotionHandler {
        bool active;
        std::string name;
        XRectangle frame;
        xlib::X11_Window* x_window;
        
        static const unsigned int left_text_margin;
        static const unsigned int top_text_margin;
        static const unsigned int frame_weight;

        Item(xlib::X11_Window* x_window, 
             bool active, 
             const std::string& name, 
             const XRectangle& frame = {});
        ~Item();
        void show_text() const;
        void show_frame() const;
        void hide_frame() const;
        void show_focus() const;
        void hide_focus() const;
        void show() const;

        int get_width() const;
        int get_height() const;

        bool focused(const int& x, const int& y) const;

        void handle_mouse_motion(const int& x, const int& y) override;
      };

    public:
      explicit GameMenu(xlib::X11_Window* x_window);
      ~GameMenu();

    public:
      void activate() override;
      void deactivate() override;
      void handle_mouse_motion(const int& x, const int& y) override;

    private:
      void update();

    private:
      xlib::X11_Window* x_window;
      std::list<Item> items;
  };
}

#endif /* SRC_INCLUDE_VIEWS_GAMEMENU_HPP */
