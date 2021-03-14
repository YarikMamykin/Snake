#ifndef SRC_INCLUDE_VIEWS_GAMEABOUT_HPP
#define SRC_INCLUDE_VIEWS_GAMEABOUT_HPP

#include "View.hpp"
#include "TextLabel.hpp"
#include "KeyPressHandler.hpp"
#include <string>
#include <memory>

namespace views {

  using namespace abstractions::ui;

  class GameAbout final : public View, 
                          public events::KeyPressHandler {
    public:
      explicit GameAbout();
      ~GameAbout() = default;

    public:
      void activate() override;
      void handle_key_press(const KeySym& key_sym, const unsigned int& mask) override;

    private:
      std::unique_ptr<TextLabel> text_label;
  };
}


#endif /* SRC_INCLUDE_VIEWS_GAMEABOUT_HPP */
