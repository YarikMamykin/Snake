#include "DrawRectangle.hpp"
#include "XlibWrapper.hpp"

namespace commands {

  DrawRectangle::DrawRectangle(const geometry::Rectangle& rectangle, const color::Color& color) 
  : GraphicsCommand(rectangle, color) { }

  DoSaveResult DrawRectangle::execute() {
    xlib::XlibWrapper::self()->draw_rectangle(std::forward<geometry::Rectangle>(rectangle), 
                                              std::forward<color::Color>(color));
    return DoSaveResult::NO;
  }

  /* constexpr */ CommandID DrawRectangle::get_id() const {
    return CommandID::DrawRectangle;
  }
}
