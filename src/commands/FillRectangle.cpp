#include "FillRectangle.hpp"
#include "XlibWrapper.hpp"

namespace commands {

  FillRectangle::FillRectangle(const geometry::Rectangle& rectangle, const color::Color& color) 
  : GraphicsCommand(rectangle, color) { }

  DoSaveResult FillRectangle::execute() {
    xlib::XlibWrapper::self()->fill_rectangle(std::forward<geometry::Rectangle>(rectangle), 
                                              std::forward<color::Color>(color));
    return DoSaveResult::NO;
  }

  /* constexpr */ CommandID FillRectangle::get_id() const {
    return CommandID::FillRectangle;
  }
}

