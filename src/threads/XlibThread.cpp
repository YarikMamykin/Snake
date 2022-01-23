#include "threads/XlibThread.hpp"
#include "events/EventDispatcher.hpp"
#include "xlib/XlibWrapper.hpp"
#include "configuration/Settings.hpp"
#include "commands/ChangeView.hpp"
#include "xlib/X11_Window.hpp"
#include <memory>
#include <thread>
#include <functional>

namespace {
  std::mutex mutex;
  std::condition_variable cv;
}

namespace threads {

  XlibThread::XlibThread(std::list<std::function<void()>>& ui_event_queue, bool& run, std::condition_variable& ui_events_available) 
  : xlib_thread(std::async(std::launch::async, [&ui_event_queue, &ui_events_available, &run, x_window = std::make_unique<xlib::X11_Window>(views::ViewID::NONE)]() {
    XInitThreads();

      using namespace configuration;
    run = xlib::XlibWrapper::self()->create_window(
        Settings::get_concrete<geometry::Rectangle>(ConfigID::WINDOW_FRAME),
        Settings::get_concrete<color::COLOR_SCHEME_TYPE>(ConfigID::WINDOW_COLOR_SCHEME),
        Settings::get_concrete_ref<unsigned int>(ConfigID::WINDOW_BORDER_WIDTH),
        Settings::get_concrete_ref<std::string>(ConfigID::WINDOW_NAME).c_str(),
        Settings::get_concrete_ref<std::string>(ConfigID::WINDOW_FONT_NAME).c_str());

    xlib::XlibWrapper::self()->select_events_to_process();

    auto* x_window_raw = x_window.get();
    events::EventDispatcher edispatcher;
    XEvent event;
    auto&& thread_sleep_timeout = config::get_concrete<std::chrono::microseconds>(config_id::THREADS_SLEEP_TIMEOUT);
    for (;run;) {
      for(auto event_type : {Expose, KeyPress, ButtonPress, MotionNotify, ClientMessage}) {
        bool event_is_in_queue = xlib::XlibWrapper::self()->event_in_queue(event_type, &event);
        if(!event_is_in_queue) {
					continue;
				}
        ui_event_queue.emplace_back(edispatcher.dispatch_event(x_window_raw, event));
      }

      ui_events_available.notify_all();

      bool queue_empty = commands::Command::xlib_queue_empty();
      if(!queue_empty) {
        std::unique_ptr<commands::Command> command = commands::Command::pop_xlib_command(); // DON'T USE auto HERE!
        command->execute();
        continue;
      } 

      std::unique_lock<std::mutex> lock(mutex);
      cv.wait_for(lock, thread_sleep_timeout, [](){return true;});
    }

    xlib::XlibWrapper::self()->destroy_window();
  })) { }

  XlibThread::~XlibThread() = default;
}
