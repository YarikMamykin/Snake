#include "QueryTextWidth.hpp"
#include <xlib/XProxy/XProxy.hpp>

namespace commands {
  QueryTextWidth::QueryTextWidth(const std::string& text, 
                                 unsigned int& result,
                                 std::atomic<bool>& trigger)
  : SynchronousCommand(trigger)
  , text(text) 
  , width(result) { }

  void QueryTextWidth::execute(xlib::XProxy& proxy) {
    width = proxy.get_text_width(text);
    trigger.store(!trigger.load());
  }

}

