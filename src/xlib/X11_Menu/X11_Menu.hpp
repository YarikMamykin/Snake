#pragma once
#include "abstractions/ui/Menu.hpp"

namespace xlib {
  class X11_Menu : public abstractions::ui::Menu {
    protected:
      unsigned int margin;
      geometry::Rectangle prev_frame;

    public:
      X11_Menu(const ::ui::LayoutType& layout, 
               const geometry::Rectangle& frame, 
               const color::COLOR_SCHEME_TYPE& color_scheme, 
               const unsigned int& spacing = 20U);

      virtual void show(bool show_flag) override;
      virtual void show_frame(bool show_flag) override;

      virtual ~X11_Menu();
  };
}

