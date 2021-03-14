#include "QueryTextHeight.hpp"
#include "XlibWrapper.hpp"

namespace commands {

  DoSaveResult QueryTextHeight::execute() {
    height = xlib::XlibWrapper::self()->get_text_height();
    return DoSaveResult::YES;
  }

  /* constexpr */ CommandID QueryTextHeight::get_id() const {
    return CommandID::QueryTextHeight;
  }

  const unsigned int QueryTextHeight::get_height() const {
    return height;
  }
}


