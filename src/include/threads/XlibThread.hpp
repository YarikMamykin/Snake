#ifndef SRC_INCLUDE_THREADING_XLIBTHREAD_HPP
#define SRC_INCLUDE_THREADING_XLIBTHREAD_HPP

#include "Window.hpp"
#include <functional>
#include <thread>
#include <list>

namespace threading {
  class XlibThread { 
    private:
      std::thread xlib_thread;
    public:
      explicit XlibThread(std::list<std::function<void()>>& ui_event_queue, 
                          abstractions::ui::AWindow* x_window_raw, 
                          bool& run);
      ~XlibThread();
  };
}

#endif /* SRC_INCLUDE_THREADING_XLIBTHREAD_HPP */
