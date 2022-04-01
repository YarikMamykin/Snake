#include "commands/graphics_commands/DrawCircle.hpp"

namespace commands {

  DrawCircle::DrawCircle(const geometry::Rectangle& circle_frame, const color::Color& color) 
  : GraphicsCommand(circle_frame, color) { }

  void DrawCircle::execute(xlib::XProxy& proxy) {
    proxy.draw_circle(rectangle, color);
  }
}
