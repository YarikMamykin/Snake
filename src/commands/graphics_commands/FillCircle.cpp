#include "commands/graphics_commands/FillCircle.hpp"
#include "xlib/XlibWrapper.hpp"

namespace commands {

  FillCircle::FillCircle(const geometry::Rectangle& circle_frame, const color::Color& color) 
  : GraphicsCommand(circle_frame, color) { }

  void FillCircle::execute() {
    xlib::XlibWrapper::self()->fill_circle(std::forward<geometry::Rectangle>(rectangle), 
                                           std::forward<color::Color>(color));
  }

}

