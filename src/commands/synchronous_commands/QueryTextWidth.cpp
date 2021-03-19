#include "QueryTextWidth.hpp"
#include "XlibWrapper.hpp"

namespace commands {
  QueryTextWidth::QueryTextWidth(const std::string& text, 
                                 unsigned int& result,
                                 std::atomic<bool>& trigger)
  : SynchronousCommand(trigger)
  , text(text) 
  , width(result) { }

  void QueryTextWidth::execute() {
    width = xlib::XlibWrapper::self()->get_text_width(text);
    trigger.store(!trigger.load());
  }

}

