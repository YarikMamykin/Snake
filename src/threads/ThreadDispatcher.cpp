#include "threads/ThreadDispatcher.hpp"

namespace threads {
  ThreadDispatcher::ThreadDispatcher() 
  : run(true)
  , xlib_thread(ui_event_queue, run) 
  , ui_thread(ui_event_queue, run) { } 

  ThreadDispatcher::~ThreadDispatcher() = default;
}
