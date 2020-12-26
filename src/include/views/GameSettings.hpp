#ifndef SRC_INCLUDE_VIEWS_GAMESETTINGS_HPP
#define SRC_INCLUDE_VIEWS_GAMESETTINGS_HPP

#include "View.hpp"
#include "X11_Window.hpp"
#include "KeyPressHandler.hpp"
#include "X11_TextLabel.hpp"
#include "AlignHandler.hpp"

#include <string>
#include <list>

namespace views {

  class GameSettings final : public View, 
                             public events::KeyPressHandler {

    private:
      typedef ui::AlignHandler<xlib::X11_TextLabel, ui::LayoutType::HORIZONTAL> LAYOUT_TYPE;
      typedef ui::AlignHandler<LAYOUT_TYPE, ui::LayoutType::VERTICAL> V_LAYOUT_TYPE;

      struct Setting {
        std::string key;
        unsigned int value;
        bool active;

        xlib::X11_TextLabel key_label;
        xlib::X11_TextLabel value_label;

        Setting(const std::string& key, unsigned int value, xlib::X11_Window* parent_window);
        void set_active(bool active);
      };

    public:
      explicit GameSettings(xlib::X11_Window* x_window);
      ~GameSettings();

    public:
      void activate() override;
      void deactivate() override;
      void handle_key_press(const KeySym&& key_sym) override;

    private:
      void update();
      void move_to_next_item();
      void move_to_prev_item();

    private:
      xlib::X11_Window* x_window;
      std::list<Setting> settings_items;
      std::list<Setting>::iterator current_active_item;
      std::list<LAYOUT_TYPE> labels_layout;
      V_LAYOUT_TYPE horizontal_layout;
  };
}


#endif /* SRC_INCLUDE_VIEWS_GAMESETTINGS_HPP */
