#include "DrawCircle.hpp"
#include "XlibWrapper.hpp"

namespace commands {

  DrawCircle::DrawCircle(const geometry::Rectangle& circle_frame, const color::Color& color) 
  : Command(circle_frame, color) { }

  void DrawCircle::execute() {
    xlib::XlibWrapper::self()->draw_circle(std::forward<geometry::Rectangle>(rectangle), 
                                           std::forward<color::Color>(color));
  }
}
