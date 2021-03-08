#include "DrawRectangle.hpp"
#include "XlibWrapper.hpp"

namespace commands {

  DrawRectangle::DrawRectangle(const geometry::Rectangle& rectangle, const color::Color& color) 
  : Command(rectangle, color) { }

  void DrawRectangle::execute() {
    xlib::XlibWrapper::self()->draw_rectangle(std::forward<geometry::Rectangle>(rectangle), 
                                              std::forward<color::Color>(color));
  }
}
