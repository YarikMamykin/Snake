#include "threads/XlibThread.hpp"
#include "events/EventDispatcher.hpp"
#include <xlib/XProxy/XProxy.hpp>
#include <xlib/XSettings.hpp>
#include <xlib/XError.hpp>
#include "configuration/Settings.hpp"
#include "commands/ChangeView/ChangeView.hpp"
#include "xlib/X11_Window/X11_Window.hpp"
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

        auto xsettings = std::make_unique<xlib::XSettings>();
        xsettings->font_name = configuration::Settings::get_concrete_ref<std::string>(configuration::ConfigID::WINDOW_FONT_NAME);
        xsettings->window_name = configuration::Settings::get_concrete_ref<std::string>(configuration::ConfigID::WINDOW_NAME);
        xsettings->border_width = configuration::Settings::get_concrete<unsigned int>(configuration::ConfigID::WINDOW_BORDER_WIDTH);
        xsettings->window_color_scheme = configuration::Settings::get_concrete_ref<color::COLOR_SCHEME_TYPE>(configuration::ConfigID::WINDOW_COLOR_SCHEME);

        auto& window_frame = configuration::Settings::get_concrete_ref<geometry::Rectangle>(configuration::ConfigID::WINDOW_FRAME);
        xsettings->window_geometry = { 
          window_frame.x,
          window_frame.y,
          window_frame.width,
          window_frame.height
        };
            
        auto xproxy_variant = xlib::XProxy::create(std::move(xsettings));

        if(std::holds_alternative<xlib::XError>(xproxy_variant)) {
          return;
        }

        auto& xproxy = std::get<std::reference_wrapper<xlib::XProxy>>(xproxy_variant).get();

    auto* x_window_raw = x_window.get();
    events::EventDispatcher edispatcher;
    XEvent event;
    auto thread_sleep_timeout = config::get_concrete<std::chrono::microseconds>(config_id::THREADS_SLEEP_TIMEOUT);
    for (;run;) {
      for(auto event_type : {Expose, KeyPress, ButtonPress, MotionNotify, ClientMessage}) {
        bool event_is_in_queue = xproxy.event_in_queue(event_type, &event);
        if(!event_is_in_queue) {
					continue;
				}
        ui_event_queue.emplace_back(edispatcher.dispatch_event(x_window_raw, event));
      }

      ui_events_available.notify_all();

      bool queue_empty = commands::Command::xlib_queue_empty();
      if(!queue_empty) {
        std::unique_ptr<commands::Command> command = commands::Command::pop_xlib_command(); // DON'T USE auto HERE!
        command->execute(xproxy);
        continue;
      } 

      std::unique_lock<std::mutex> lock(mutex);
      cv.wait_for(lock, thread_sleep_timeout, [](){return true;});
    }

  })) { }

  XlibThread::~XlibThread() = default;
}
