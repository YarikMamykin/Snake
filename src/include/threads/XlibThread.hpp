#ifndef SRC_INCLUDE_THREADS_XLIBTHREAD_HPP
#define SRC_INCLUDE_THREADS_XLIBTHREAD_HPP
#include "abstractions/ui/Window.hpp"
#include <functional>
#include <future>
#include <list>

namespace threads {
  class XlibThread { 
    private:
      std::future<void> xlib_thread;

    public:
      explicit XlibThread(std::list<std::function<void()>>& ui_event_queue, bool& run);
      ~XlibThread();
  };
}


#endif /* SRC_INCLUDE_THREADS_XLIBTHREAD_HPP */
