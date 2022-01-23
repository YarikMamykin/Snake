#include "threads/ThreadDispatcher.hpp"

namespace threads {
  ThreadDispatcher::ThreadDispatcher() 
  : run(true)
  , xlib_thread(ui_event_queue, run, ui_events_available) 
  , ui_thread(ui_event_queue, run, ui_events_available) { } 

  ThreadDispatcher::~ThreadDispatcher() = default;
}
