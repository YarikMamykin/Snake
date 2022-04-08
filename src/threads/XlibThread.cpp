#include "threads/XlibThread.hpp"
#include "events/EventDispatcher/EventDispatcher.hpp"
#include <mutex>
#include <xlib/XProxy/XProxy.hpp>
#include <xlib/XSettings.hpp>
#include <xlib/XError.hpp>
#include "configuration/Settings.hpp"
#include "commands/ChangeView/ChangeView.hpp"
#include <abstractions/ui/Window.hpp>
#include <memory>
#include <thread>
#include <functional>
#include <future>
#include "UI_EventQueue.hpp"

namespace {

  std::variant<std::reference_wrapper<xlib::XProxy>, xlib::XError> xproxy_variant { xlib::XError::NONE };
}

namespace threads {

  XlibThread::XlibThread() = default;
  XlibThread::~XlibThread() = default;

  bool XlibThread::init() const noexcept {

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

    xproxy_variant = xlib::XProxy::create(std::move(xsettings));

    return !std::holds_alternative<xlib::XError>(xproxy_variant);
  }

  void XlibThread::run(
      UI_EventQueue& ui_event_queue, 
      std::mutex& sync_mutex, 
      std::shared_ptr<abstractions::ui::AWindow> x_window,
      std::condition_variable& ui_events_available) noexcept {

    auto runner = [ &ui_event_queue, &sync_mutex, x_window, &ui_events_available ]() mutable noexcept {

      auto& xproxy = std::get<std::reference_wrapper<xlib::XProxy>>(xproxy_variant).get();

      commands::Command::push_xlib_command(std::make_unique<commands::ChangeView>(views::ViewID::MENU));
      events::EventDispatcher edispatcher;

      auto thread_sleep_timeout = config::get_concrete<std::chrono::microseconds>(config_id::THREADS_SLEEP_TIMEOUT);
      while(!x_window->closing()) {

        for(auto event_type : {Expose, KeyPress, ButtonPress, MotionNotify, ClientMessage}) {

          XEvent event;

          bool event_is_in_queue = xproxy.event_in_queue(event_type, &event);
          if(!event_is_in_queue) {
            continue;
          }

          // ui_event_queue.push(edispatcher.dispatch_event(x_window, event));
          edispatcher.dispatch_event(x_window, event)();
        }

        bool queue_empty = commands::Command::xlib_queue_empty();
        if(!queue_empty) {
          std::unique_ptr<commands::Command> command = commands::Command::pop_xlib_command(); // DON'T USE auto HERE!
          command->execute(xproxy);
          continue;
        }
      }

    };

    m_handler = std::async(std::launch::deferred, runner);
    m_handler.wait();
  }

}
