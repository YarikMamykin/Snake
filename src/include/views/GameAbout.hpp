#ifndef SRC_INCLUDE_VIEWS_GAMEABOUT_HPP
#define SRC_INCLUDE_VIEWS_GAMEABOUT_HPP

#include "View.hpp"
#include "X11_Window.hpp"
#include "X11_TextLabel.hpp"
#include "KeyPressHandler.hpp"
#include <string>

namespace views {

  class GameAbout final : public View, 
                          public events::KeyPressHandler {
    public:
      explicit GameAbout();
      ~GameAbout() = default;

    public:
      void activate() override;
      void handle_key_press(const KeySym&& key_sym, const unsigned int&& mask) override;

    private:
      xlib::X11_Window* x_window;
      xlib::X11_TextLabel text_label;
  };
}


#endif /* SRC_INCLUDE_VIEWS_GAMEABOUT_HPP */
