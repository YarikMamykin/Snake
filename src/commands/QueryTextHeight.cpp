#include "QueryTextHeight.hpp"
#include "XlibWrapper.hpp"

namespace commands {

  QueryTextHeight::QueryTextHeight(unsigned int& result, std::atomic<bool>& trigger) 
  : SynchronousCommand(trigger)
  , height(result) { }

  DoSaveResult QueryTextHeight::execute() {
    height = xlib::XlibWrapper::self()->get_text_height();
    trigger.store(!trigger.load());
    return DoSaveResult::YES;
  }

  constexpr CommandID QueryTextHeight::get_id() const {
    return CommandID::QueryTextHeight;
  }
}


