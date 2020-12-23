#ifndef SRC_INCLUDE_VIEWS_GAMEOVER_HPP
#define SRC_INCLUDE_VIEWS_GAMEOVER_HPP

#include "View.hpp"
#include "X11_Window.hpp"
#include "KeyPressHandler.hpp"
#include "UI_Object.hpp"
#include <string>

namespace views {

  class GameOver final : public ui::UI_Object,
                         public View, 
                         public events::KeyPressHandler {
    public:
      explicit GameOver(xlib::X11_Window* x_window);
      ~GameOver() = default;

    public:
      void activate() override;
      void deactivate() override;
      void handle_key_press(const KeySym&& key_sym) override;

    private:
      xlib::X11_Window* x_window;
      std::string text;
  };
}

#endif /* SRC_INCLUDE_VIEWS_GAMEOVER_HPP */
