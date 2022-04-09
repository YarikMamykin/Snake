#pragma once
#include <xlib/X11_Menu/X11_Menu.hpp>
#include <functional>
#include <memory>


namespace abstractions::ui {
  class TextLabel;
  class Object;
}

namespace views {

  struct Setting : public xlib::X11_Menu {
    Setting(std::unique_ptr<abstractions::ui::TextLabel> key_presenter, 
        std::unique_ptr<abstractions::ui::Object> value_presenter,
        std::function<void()> increase_binder, 
        std::function<void()> decrease_binder);

    void increase();
    void decrease();

    std::function<void()> increase_binder, decrease_binder;
  };

}
