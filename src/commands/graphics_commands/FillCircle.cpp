#include "commands/graphics_commands/FillCircle.hpp"

namespace commands {

  FillCircle::FillCircle(const geometry::Rectangle& circle_frame, const color::Color& color) 
  : GraphicsCommand(circle_frame, color) { }

  void FillCircle::execute(xlib::XProxy& proxy) {
    proxy.fill_circle(rectangle, color);
  }
}

