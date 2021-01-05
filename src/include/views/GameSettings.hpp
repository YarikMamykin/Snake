#ifndef SRC_INCLUDE_VIEWS_GAMESETTINGS_HPP
#define SRC_INCLUDE_VIEWS_GAMESETTINGS_HPP

#include "View.hpp"
#include "X11_Window.hpp"
#include "KeyPressHandler.hpp"
#include "X11_TextLabel.hpp"
#include "X11_Menu.hpp"

#include <string>
#include <memory>

namespace views {

  class GameSettings final : public View, 
                             public events::KeyPressHandler {

    private:
      struct Setting : public xlib::X11_Menu {
        Setting(std::unique_ptr<abstractions::ui::TextLabel> key_presenter, 
                std::unique_ptr<abstractions::ui::Object> value_presenter,
                xlib::X11_Window* x_window);

        void increase();
        void decrease();

        std::function<void()> increase_binder;
        std::function<void()> decrease_binder;
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
      template<typename ValuePresenterType, typename ValueType, typename ValuePresentingObjectType> std::unique_ptr<xlib::X11_Menu>
        construct_menu_item(const std::string& name, const ValueType& value, 
                            const abstractions::ui::COLOR_SCHEME_TYPE& key_color_scheme,
                            const abstractions::ui::COLOR_SCHEME_TYPE& value_color_scheme,
                            std::unique_ptr<ValuePresentingObjectType> value_presenting_ui_object,
                            xlib::X11_Window* x_window) {
          std::unique_ptr<xlib::X11_TextLabel> key_presenter(new xlib::X11_TextLabel(name, {}, key_color_scheme, x_window));
          std::unique_ptr<ValuePresenterType> value_presenter(new ValuePresenterType(value, std::move(value_presenting_ui_object)));

          auto increase_binder = value_presenter->bind_increase_value_trigger();
          auto decrease_binder = value_presenter->bind_decrease_value_trigger();

          auto setting = new Setting(std::move(key_presenter), std::move(value_presenter), x_window);

          setting->increase_binder = increase_binder;
          setting->decrease_binder = decrease_binder;

          std::unique_ptr<xlib::X11_Menu> menu_item(setting);
          return menu_item;
        }

    private:
      xlib::X11_Window* x_window;
      xlib::X11_Menu menu;
  };
}


#endif /* SRC_INCLUDE_VIEWS_GAMESETTINGS_HPP */
