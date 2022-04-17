#pragma once

#include "abstractions/views/View.hpp"
#include "abstractions/ui/TextLabel.hpp"
#include "events/event_handlers/KeyPressHandler.hpp"
#include <string>
#include <memory>

namespace views {

  using namespace abstractions::ui;

  class GameAbout : public View, 
                    public events::KeyPressHandler {

      std::unique_ptr<TextLabel> text_label;

    public:

      // For testing
      explicit GameAbout(TextLabel* tlabel = nullptr);
      ~GameAbout() = default;

      void activate() override;
      void handle_key_press(const KeySym& key_sym, const unsigned int& mask) override;
  };
}
