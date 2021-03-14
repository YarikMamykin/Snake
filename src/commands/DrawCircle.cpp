#include "DrawCircle.hpp"
#include "XlibWrapper.hpp"

namespace commands {

  DrawCircle::DrawCircle(const geometry::Rectangle& circle_frame, const color::Color& color) 
  : GraphicsCommand(circle_frame, color) { }

  DoSaveResult DrawCircle::execute() {
    xlib::XlibWrapper::self()->draw_circle(std::forward<geometry::Rectangle>(rectangle), 
                                           std::forward<color::Color>(color));
    return DoSaveResult::NO;
  }

  /* constexpr */ CommandID DrawCircle::get_id() const {
    return CommandID::DrawCircle;
  }
}
