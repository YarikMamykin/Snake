#ifndef SRC_INCLUDE_VIEWS_GAMEMENU_HPP
#define SRC_INCLUDE_VIEWS_GAMEMENU_HPP
#include "abstractions/views/View.hpp"
#include <list>
#include <functional>
#include <memory>
#include "abstractions/event_handling/KeyPressHandler.hpp"
#include "xlib/X11_TextLabel.hpp"

namespace abstractions::ui {
  class Menu;
}

namespace views {

  class GameMenu : public View, 
                   public events::KeyPressHandler {
    private:
      class Item : public xlib::X11_TextLabel {
        std::function<void()> activation_callback;

        public:
          Item(const std::string& name, std::function<void()> activation_callback);
          ~Item() = default;
          void activate();
      };

    public:
      explicit GameMenu();
      ~GameMenu() override = default;

    public:
      void activate() override;
      void handle_key_press(const KeySym& key_sym, const unsigned int& mask) override;

    private:
      void update();
      void move_to_next_item();
      void move_to_prev_item();

      static Item* current_item_as_game_menu_item(const abstractions::ui::Menu& menu);

    private:
      std::unique_ptr<abstractions::ui::Menu> menu;
  };
}


#endif /* SRC_INCLUDE_VIEWS_GAMEMENU_HPP */
