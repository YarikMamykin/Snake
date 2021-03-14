#include "QueryTextWidth.hpp"
#include "XlibWrapper.hpp"

namespace commands {
  QueryTextWidth::QueryTextWidth(const std::string& text)
  : width(0u)
  , text(text) { }

  DoSaveResult QueryTextWidth::execute() {
    width = xlib::XlibWrapper::self()->get_text_width(text);
    return DoSaveResult::YES;
  }

  /* constexpr */ CommandID QueryTextWidth::get_id() const {
    return CommandID::QueryTextWidth;
  }

  const unsigned int QueryTextWidth::get_width() const {
    return width;
  }
}

