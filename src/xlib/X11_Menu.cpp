#include "X11_Menu.hpp"
#include <iostream>

namespace {
  
}

namespace xlib {
  X11_Menu::X11_Menu(const ::ui::LayoutType& layout, 
                     const geometry::Rectangle& frame, 
                     const abstractions::ui::COLOR_SCHEME_TYPE& color_scheme,
                     xlib::X11_Window* x_window,
                     const unsigned int& spacing)
    : abstractions::ui::Menu(layout, frame, color_scheme, spacing) 
    , x_window(x_window) 
    , margin(20U) {}

  void X11_Menu::show(bool show_flag) {
    abstractions::ui::Menu::show(show_flag);
    show_frame(focused());
  }

  void X11_Menu::show_frame(bool show_flag) {
    update_menu_frame();
    if(show_flag) {
      auto& display = x_window->x_display.display;
      auto& graphical_context = x_window->graphical_context;
      auto& window = x_window->window;
      XSetForeground(display, graphical_context, this->color_scheme[ui::ColorSchemeID::FrameColor]);
      XDrawRectangle(display, window, graphical_context, 
          this->frame.x - margin, 
          this->frame.y - margin, 
          this->frame.width + margin * 2, 
          this->frame.height + margin * 2);
    }

    if(!show_flag) {
      auto& display = x_window->x_display.display;
      auto& graphical_context = x_window->graphical_context;
      auto& window = x_window->window;
      XSetForeground(display, graphical_context, this->color_scheme[ui::ColorSchemeID::BackgroundColor]);
      XDrawRectangle(display, window, graphical_context, 
          this->frame.x - margin, 
          this->frame.y - margin, 
          this->frame.width + margin * 2, 
          this->frame.height + margin * 2);
    }
  }

  X11_Menu::~X11_Menu() {}
}
