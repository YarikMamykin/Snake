#pragma once

#include <xlib/X11_TextLabel/X11_TextLabel.hpp>
#include <functional>

namespace views {

      class Item : public xlib::X11_TextLabel {

        std::function<void()> activation_callback;

        public:
          Item(
              const std::string& name, 
              std::function<void()> activation_callback);
          ~Item();

          void activate();
      };
}
