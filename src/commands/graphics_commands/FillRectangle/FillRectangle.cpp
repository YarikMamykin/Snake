#include "FillRectangle.hpp"
#include <xlib/XProxy/XProxy.hpp>

namespace commands {

  FillRectangle::FillRectangle(const geometry::Rectangle& rectangle, const color::Color& color) 
  : GraphicsCommand(rectangle, color) { }

  void FillRectangle::execute(xlib::XProxy& proxy) {
    proxy.fill_rectangle(rectangle, color);
  }
}

