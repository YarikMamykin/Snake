#include "commands/graphics_commands/DrawRectangle.hpp"
#include "xlib/XlibWrapper.hpp"

namespace commands {

  DrawRectangle::DrawRectangle(const geometry::Rectangle& rectangle, const color::Color& color) 
  : GraphicsCommand(rectangle, color) { }

  void DrawRectangle::execute() {
    xlib::XlibWrapper::self()->draw_rectangle(std::forward<geometry::Rectangle>(rectangle), 
                                              std::forward<color::Color>(color));
  }

}
