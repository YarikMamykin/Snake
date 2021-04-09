#include "threads/UI_Thread.hpp"
#include "configuration/Settings.hpp"

namespace threading {
  UI_Thread::UI_Thread(std::list<std::function<void()>>& ui_event_queue, bool& run) 
  : ui_thread([&ui_event_queue, &run]() {
    try {
      auto&& thread_sleep_timeout = config::get_concrete<std::chrono::microseconds>(config_id::THREADS_SLEEP_TIMEOUT);
      for(;run;) {
        if(!ui_event_queue.empty()) {
          ui_event_queue.front()();
          ui_event_queue.pop_front();
        } else {
          std::this_thread::sleep_for(thread_sleep_timeout);
        }
      }
    } catch(...) {
			run = false;
    }
  }) { }

  UI_Thread::~UI_Thread() {
    ui_thread.join();
  }
}
