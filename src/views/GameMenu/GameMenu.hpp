#pragma once

#include "abstractions/views/View.hpp"
#include "events/event_handlers/KeyPressHandler.hpp"
#include <list>
#include <memory>
#include "events/event_handlers/KeyPressHandler.hpp"
#include <xlib/X11_TextLabel/X11_TextLabel.hpp>
#include <abstractions/ui/Menu.hpp>

namespace views {
  class Item;
}

namespace views {

  class GameMenu : public View, 
                   public events::KeyPressHandler {

    std::unique_ptr<abstractions::ui::Menu> menu;

    void update();

    static Item* 
      current_item_as_game_menu_item(const abstractions::ui::Menu& menu);

    public:
      explicit GameMenu();
      ~GameMenu() override = default;

      void activate() override;
      void handle_key_press(
          const KeySym& key_sym, 
          const unsigned int& mask) override;

  };
}
