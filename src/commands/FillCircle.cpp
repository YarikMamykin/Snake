#include "FillCircle.hpp"
#include "XlibWrapper.hpp"

namespace commands {

  FillCircle::FillCircle(const geometry::Rectangle& circle_frame, const color::Color& color) 
  : GraphicsCommand(circle_frame, color) { }

  DoSaveResult FillCircle::execute() {
    xlib::XlibWrapper::self()->fill_circle(std::forward<geometry::Rectangle>(rectangle), 
                                           std::forward<color::Color>(color));
    return DoSaveResult::NO;
  }

  constexpr CommandID FillCircle::get_id() const {
    return CommandID::FillCircle;
  }
}

