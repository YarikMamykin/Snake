#ifndef SRC_INCLUDE_VIEWS_GAMESETTINGS_HPP
#define SRC_INCLUDE_VIEWS_GAMESETTINGS_HPP
#include "abstractions/views/View.hpp"
#include "abstractions/event_handling/KeyPressHandler.hpp"
#include "xlib/X11_TextLabel.hpp"
#include "xlib/X11_Menu.hpp"
#include <string>
#include <memory>

namespace views {

  class GameSettings : public View, 
                       public events::KeyPressHandler {

    private:
      struct Setting : public xlib::X11_Menu {
        Setting(std::unique_ptr<abstractions::ui::TextLabel> key_presenter, 
                std::unique_ptr<abstractions::ui::Object> value_presenter,
                std::function<void()> increase_binder, 
                std::function<void()> decrease_binder);

        void increase();
        void decrease();

        std::function<void()> increase_binder, decrease_binder;
      };

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



#endif /* SRC_INCLUDE_VIEWS_GAMESETTINGS_HPP */
