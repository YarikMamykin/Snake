#ifndef SRC_INCLUDE_VIEWS_GAMEMENU_HPP
#define SRC_INCLUDE_VIEWS_GAMEMENU_HPP

#include "View.hpp"
#include "UI_Object.hpp"
#include "X11_Window.hpp"
#include <list>
#include <functional>
#include "MouseMotionHandler.hpp"
#include "MouseButtonPressHandler.hpp"
#include "KeyPressHandler.hpp"

namespace views {

  class GameMenu final : public View, 
                         public events::MouseMotionHandler, 
                         public events::MouseButtonPressHandler, 
                         public events::KeyPressHandler {
    private:
      struct Item : public events::MouseMotionHandler, 
                    public events::MouseButtonPressHandler,
                    public events::KeyPressHandler {
        bool active;
        std::string name;
        XRectangle frame;
        xlib::X11_Window* x_window;

        std::function<bool(Item&)> mouse_button_press_handler;
        std::function<bool(Item&)> mouse_motion_handler;
        std::function<bool(Item&)> key_press_handler;

        static const unsigned int left_text_margin;
        static const unsigned int top_text_margin;
        static const unsigned int frame_weight;

        Item(xlib::X11_Window* x_window, 
             bool active, 
             const std::string& name, 
             const XRectangle& frame,
             std::function<bool(Item&)> mouse_button_press_handler,
             std::function<bool(Item&)> mouse_motion_handler,
             std::function<bool(Item&)> key_press_handler);
        ~Item();
        void show_text() const;
        void show_frame() const;
        void hide_frame() const;
        void show_focus();
        void hide_focus();
        void show() const;

        int get_width() const;
        int get_height() const;

        bool focused(const int& x, const int& y) const;

        void handle_mouse_motion(const int& x, const int& y) override;
        void handle_button_press(const int& x, const int& y, const unsigned int& button) override;
        void handle_key_press(const KeySym&& key_sym) override;
      };

    public:
      explicit GameMenu(xlib::X11_Window* x_window);
      ~GameMenu();

    public:
      void activate() override;
      void deactivate() override;
      void handle_mouse_motion(const int& x, const int& y) override;
      void handle_button_press(const int& x, const int& y, const unsigned int& button) override;
      void handle_key_press(const KeySym&& key_sym) override;

    private:
      void update();

    private:
      xlib::X11_Window* x_window;
      std::list<Item> items;
  };
}

#endif /* SRC_INCLUDE_VIEWS_GAMEMENU_HPP */
