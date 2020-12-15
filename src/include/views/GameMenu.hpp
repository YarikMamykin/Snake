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
#include "Rectangle.hpp"

namespace views {

  class GameMenu final : public ui::UI_Object,
                         public View, 
                         public events::MouseMotionHandler, 
                         public events::MouseButtonPressHandler, 
                         public events::KeyPressHandler {
    private:
      struct Item {
        bool active;
        std::string name;
        geometry::Rectangle frame;
        xlib::X11_Window* x_window;

        typedef std::function<void(const int& x, const int& y, const unsigned int& button)> MOUSE_BUTTON_PRESS_HANDLER_TYPE;
        typedef std::function<void(const int& x, const int& y)> MOUSE_MOTION_HANDLER_TYPE;
        typedef std::function<void(const KeySym&& key_sym)> KEY_PRESS_HANDLER_TYPE;
        typedef std::vector<std::string> ITEMS_NAMES_VECTOR_TYPE;
        typedef std::tuple<std::string, 
                MOUSE_MOTION_HANDLER_TYPE, 
                MOUSE_BUTTON_PRESS_HANDLER_TYPE, 
                KEY_PRESS_HANDLER_TYPE> ITEMS_EVENT_HANDLERS_TYPE;
        typedef std::vector<ITEMS_EVENT_HANDLERS_TYPE> ITEMS_EVENT_HANDLERS_VECTOR_TYPE;

        MOUSE_BUTTON_PRESS_HANDLER_TYPE mouse_button_press_handler;
        MOUSE_MOTION_HANDLER_TYPE mouse_motion_handler;
        KEY_PRESS_HANDLER_TYPE key_press_handler;

        static const unsigned int left_text_margin;
        static const unsigned int top_text_margin;
        static const unsigned int frame_weight;

        Item(xlib::X11_Window* x_window, 
             bool active, 
             const std::string& name, 
             const geometry::Rectangle& frame,
             MOUSE_MOTION_HANDLER_TYPE mouse_motion_handler,
             MOUSE_BUTTON_PRESS_HANDLER_TYPE mouse_button_press_handler,
             KEY_PRESS_HANDLER_TYPE key_press_handler);
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

        void handle_mouse_motion(const int& x, const int& y);
        void handle_button_press(const int& x, const int& y, const unsigned int& button);
        void handle_key_press(const KeySym&& key_sym);
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
      const int get_event_handling_mask() const override;

    private:
      void update();

    private:
      xlib::X11_Window* x_window;
      std::list<Item> items;
  };
}

#endif /* SRC_INCLUDE_VIEWS_GAMEMENU_HPP */
