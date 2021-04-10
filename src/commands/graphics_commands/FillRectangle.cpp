#include "commands/graphics_commands/FillRectangle.hpp"
#include "xlib/XlibWrapper.hpp"

namespace commands {

  FillRectangle::FillRectangle(const geometry::Rectangle& rectangle, const color::Color& color) 
  : GraphicsCommand(rectangle, color) { }

  void FillRectangle::execute() {
    xlib::XlibWrapper::self()->fill_rectangle(rectangle, color);
  }
}

