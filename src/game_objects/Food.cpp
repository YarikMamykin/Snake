#include "Food.hpp"

namespace game_objects {

  Food::Food(xlib::X11_Window* x_window, const color::Color&& color, geometry::Rectangle&& frame) 
  : x_window(x_window) 
  , color(color) 
  , frame(std::forward<decltype(frame)>(frame)) { }

  Food::~Food() {
    // XSetForeground(x_window->x_display.display, x_window->graphical_context, this->color_scheme.at(color::ColorSchemeID::BackgroundColor).to_long());
    // XFillRectangle(x_window->x_display.display,
        // x_window->window,
        // x_window->graphical_context,
        // frame.x,
        // frame.y,
        // frame.width,
        // frame.height);
    // XFlush(x_window->x_display.display);
  }

  void Food::show() {
//     XSetForeground(x_window->x_display.display, x_window->graphical_context, this->color_scheme.at(color::ColorSchemeID::BackgroundColor).to_long());
    // XFillRectangle(x_window->x_display.display,
        // x_window->window,
        // x_window->graphical_context,
        // frame.x,
        // frame.y,
        // frame.width,
        // frame.height);
    // XSetForeground(x_window->x_display.display, x_window->graphical_context, this->color_scheme.at(color::ColorSchemeID::FoodColor).to_long());
    // XDrawArc(x_window->x_display.display,
        // x_window->window,
        // x_window->graphical_context,
        // frame.x,
        // frame.y,
        // frame.width,
        // frame.height,
        // 0, 360*64); // angle is specified as <degrees> * 64
    // XFlush(x_window->x_display.display);
  }
}
