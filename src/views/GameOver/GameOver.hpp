#pragma once

#include "abstractions/views/View.hpp"
#include <xlib/X11_ColorizedTextLabel/X11_ColorizedTextLabel.hpp>
#include "timing/Timer.hpp"
#include "events/event_handlers/KeyPressHandler.hpp"
#include <string>

namespace views {

  class GameOver : public View, 
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
