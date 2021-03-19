#include "XlibThread.hpp"
#include "EventDispatcher.hpp"
#include "XlibWrapper.hpp"
#include "Settings.hpp"
#include "ChangeView.hpp"
#include <memory>
#include <thread>
#include <functional>

namespace threading {

  XlibThread::XlibThread(std::list<std::function<void()>>& ui_event_queue, abstractions::ui::AWindow* x_window_raw, bool& run) 
  : xlib_thread([&ui_event_queue, x_window_raw, &run]() {
    XInitThreads();

      using namespace configuration;
    xlib::XlibWrapper::self()->create_window(
        Settings::get_concrete<geometry::Rectangle>(ConfigID::WINDOW_FRAME),
        Settings::get_concrete<color::COLOR_SCHEME_TYPE>(ConfigID::WINDOW_COLOR_SCHEME),
        Settings::get_concrete<unsigned int>(ConfigID::WINDOW_BORDER_WIDTH),
        Settings::get_concrete<std::string>(ConfigID::WINDOW_NAME).c_str(),
        Settings::get_concrete<std::string>(ConfigID::WINDOW_FONT_NAME).c_str());

    xlib::XlibWrapper::self()->select_events_to_process();

    events::EventDispatcher edispatcher;
    XEvent event;
    for (;run;) {
      for(auto event_type : {Expose, KeyPress, ButtonPress, MotionNotify, ClientMessage}) {
        bool event_is_in_queue = xlib::XlibWrapper::self()->event_in_queue(event_type, &event);
        if(!event_is_in_queue) {
					continue;
				}
        ui_event_queue.emplace_back(edispatcher.dispatch_event(x_window_raw, event));
      }

      bool queue_empty = commands::Command::xlib_queue_empty();
      if(!queue_empty) {
        std::unique_ptr<commands::Command> command = commands::Command::pop_xlib_command(); // DON'T USE auto HERE!
        command->execute();
      }
    }

    xlib::XlibWrapper::self()->destroy_window();
  }) { }

  XlibThread::~XlibThread() {
    xlib_thread.join();
  }
}
