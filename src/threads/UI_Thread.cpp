#include "threads/UI_Thread.hpp"
#include "configuration/Settings.hpp"
#include "commands/ChangeView.hpp"
#include <mutex>
#include <condition_variable>

namespace {
  std::mutex mutex;
  std::condition_variable cv;
}

namespace threads {
  UI_Thread::UI_Thread(std::list<std::function<void()>>& ui_event_queue, bool& run, std::condition_variable& ui_events_available) 
  : run(run)
  , ui_thread(std::async(std::launch::async, [&ui_event_queue, &run]() {
      auto&& thread_sleep_timeout = config::get_concrete<std::chrono::microseconds>(config_id::THREADS_SLEEP_TIMEOUT);
      commands::Command::push_xlib_command(std::make_unique<commands::ChangeView>(views::ViewID::MENU));
      for(;run;) {
        std::unique_lock<std::mutex> lock(mutex);
        if(cv.wait_for(lock, thread_sleep_timeout, [&ui_event_queue](){return !ui_event_queue.empty();})) {
          ui_event_queue.front()();
          ui_event_queue.pop_front();
        } 
      }
    })) { }

  UI_Thread::~UI_Thread() {
    try { ui_thread.get(); }
    catch(...) { run = false; }
  }
}
