#include "QueryTextHeight.hpp"
#include <xlib/XProxy/XProxy.hpp>

namespace commands {

  QueryTextHeight::QueryTextHeight(unsigned int& result, QueryLock& ql) 
  : SynchronousCommand(ql)
  , height(result) { }

  void QueryTextHeight::execute(xlib::XProxy& proxy) {
    height = proxy.get_text_height();
  }
}


