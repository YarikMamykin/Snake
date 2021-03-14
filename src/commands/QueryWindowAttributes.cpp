#include "QueryWindowAttributes.hpp"
#include "XlibWrapper.hpp"

namespace commands {
  DoSaveResult QueryWindowAttributes::execute() {
    attributes = xlib::XlibWrapper::self()->get_window_attributes();
    return DoSaveResult::YES;
  }

  /* constexpr */ CommandID QueryWindowAttributes::get_id() const {
    return CommandID::QueryWindowAttributes;
  }

  const XWindowAttributes& QueryWindowAttributes::get_window_attributes() const {
    return attributes;
  }
}
