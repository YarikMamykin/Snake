#include "commands/graphics_commands/DrawCircle.hpp"
#include "xlib/XlibWrapper.hpp"

namespace commands {

  DrawCircle::DrawCircle(const geometry::Rectangle& circle_frame, const color::Color& color) 
  : GraphicsCommand(circle_frame, color) { }

  void DrawCircle::execute() {
    xlib::XlibWrapper::self()->draw_circle(rectangle, color);
  }
}
