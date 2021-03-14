#ifndef SRC_INCLUDE_VIEWS_GAMEOVER_HPP
#define SRC_INCLUDE_VIEWS_GAMEOVER_HPP

#include "View.hpp"
#include "X11_ColorizedTextLabel.hpp"
#include "Timer.hpp"
#include "KeyPressHandler.hpp"
#include <string>

namespace views {

  class GameOver final : public View, 
                         public events::KeyPressHandler {
    public:
      explicit GameOver();
      ~GameOver();

    public:
      void activate() override;
      void handle_key_press(const KeySym& key_sym, const unsigned int& mask) override;

    private:
      std::unique_ptr<xlib::X11_ColorizedTextLabel> colorized_text_label;
      timing::Timer timer;
  };
}

#endif /* SRC_INCLUDE_VIEWS_GAMEOVER_HPP */
