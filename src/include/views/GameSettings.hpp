#ifndef SRC_INCLUDE_VIEWS_GAMESETTINGS_HPP
#define SRC_INCLUDE_VIEWS_GAMESETTINGS_HPP

#include "View.hpp"
#include "UI_Object.hpp"
#include "X11_Window.hpp"
#include "KeyPressHandler.hpp"
#include "X11_TextLabel.hpp"

#include <string>
#include <list>

namespace views {

  class GameSettings final : public ui::UI_Object,
                             public View, 
                             public events::KeyPressHandler {

    private:
      struct Setting {
        std::string key;
        unsigned int value;
        bool active;

        xlib::X11_TextLabel key_label;
        xlib::X11_TextLabel value_label;

        Setting(const std::string& key, unsigned int value, xlib::X11_Window* parent_window);
        void show();
        void set_active(bool active);
        void move(const int& x, const int& y);
      };

    public:
      explicit GameSettings(xlib::X11_Window* x_window);
      ~GameSettings();

    public:
      void activate() override;
      void deactivate() override;
      void handle_key_press(const KeySym&& key_sym) override;
      const int get_event_handling_mask() const override;

    private:
      xlib::X11_Window* x_window;
      std::list<Setting> settings_items;
  };
}


#endif /* SRC_INCLUDE_VIEWS_GAMESETTINGS_HPP */
