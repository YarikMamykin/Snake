#include "commands/graphics_commands/DrawRectangle.hpp"

namespace commands {

  DrawRectangle::DrawRectangle(const geometry::Rectangle& rectangle, const color::Color& color) 
  : GraphicsCommand(rectangle, color) { }

  void DrawRectangle::execute(xlib::XProxy& proxy) {
    proxy.draw_rectangle(rectangle, color);
  }
}
