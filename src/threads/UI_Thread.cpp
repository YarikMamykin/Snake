#include "UI_Thread.hpp"

namespace threading {
  UI_Thread::UI_Thread(std::list<std::function<void()>>& ui_event_queue, bool& run) 
  : ui_thread([&ui_event_queue, &run]() {
    try {
      for(;run;) {
        if(!ui_event_queue.empty()) {
          ui_event_queue.front()();
          ui_event_queue.pop_front();
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
