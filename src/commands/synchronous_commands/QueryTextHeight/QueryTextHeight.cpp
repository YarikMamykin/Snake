#include "QueryTextHeight.hpp"
#include <xlib/XProxy/XProxy.hpp>

namespace commands {

  QueryTextHeight::QueryTextHeight(unsigned int& result, std::atomic<bool>& trigger) 
  : SynchronousCommand(trigger)
  , height(result) { }

  void QueryTextHeight::execute(xlib::XProxy& proxy) {
    height = proxy.get_text_height();
    trigger.store(!trigger.load());
  }

}

