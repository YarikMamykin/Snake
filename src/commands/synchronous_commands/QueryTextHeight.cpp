#include "commands/synchronous_commands/QueryTextHeight.hpp"
#include "xlib/XlibWrapper.hpp"

namespace commands {

  QueryTextHeight::QueryTextHeight(unsigned int& result, std::atomic<bool>& trigger) 
  : SynchronousCommand(trigger)
  , height(result) { }

  void QueryTextHeight::execute() {
    height = xlib::XlibWrapper::self()->get_text_height();
    trigger.store(!trigger.load());
  }

}


