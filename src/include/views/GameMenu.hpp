#ifndef SRC_INCLUDE_VIEWS_GAMEMENU_HPP
#define SRC_INCLUDE_VIEWS_GAMEMENU_HPP

#include "View.hpp"
#include "X11_Window.hpp"
#include "X11_TextLabel.hpp"
#include <list>
#include <functional>
#include "KeyPressHandler.hpp"
#include "X11_Menu.hpp"

namespace views {

  class GameMenu final : public View, 
                         public events::KeyPressHandler {
    private:
      struct Item : public xlib::X11_TextLabel,
                    public events::KeyPressHandler {

        typedef std::function<void(const KeySym&& key_sym)> KEY_PRESS_HANDLER_TYPE;
        Item(xlib::X11_Window* x_window, 
             const std::string& name, 
             KEY_PRESS_HANDLER_TYPE key_press_handler);
        ~Item();

        void handle_key_press(const KeySym&& key_sym, const unsigned int&& mask);
         KEY_PRESS_HANDLER_TYPE key_press_handler;
      };

    public:
      explicit GameMenu(xlib::X11_Window* x_window);
      ~GameMenu();

    public:
      void activate() override;
      void handle_key_press(const KeySym&& key_sym, const unsigned int&& mask) override;
      const int get_event_handling_mask() const override;

    private:
      void update();
      void move_to_next_item();
      void move_to_prev_item();

      static events::KeyPressHandler* current_item_as_key_press_handler(const xlib::X11_Menu& menu);

    private:
      xlib::X11_Window* parent_window;
      xlib::X11_Menu menu;
  };
}

#endif /* SRC_INCLUDE_VIEWS_GAMEMENU_HPP */
