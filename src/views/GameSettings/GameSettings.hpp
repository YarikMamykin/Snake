#pragma once 

#include "abstractions/views/View.hpp"
#include "events/event_handlers/KeyPressHandler.hpp"
#include <string>
#include <memory>

namespace abstractions::ui {
  class Menu;
}

namespace views {

  struct Setting;

  class GameSettings : public View, 
                       public events::KeyPressHandler {

    public:
      explicit GameSettings();
      ~GameSettings() = default;

    public:
      void activate() override;
      void handle_key_press(const KeySym& key_sym, const unsigned int& mask) override;

    private:
      void update();
      static Setting* current_item_as_setting(const abstractions::ui::Menu& menu);

    private:
      std::unique_ptr<abstractions::ui::Menu> menu;
  };
}
