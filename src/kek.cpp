/*
   Simple Xlib application for creating a window and drawing a box in it.
   gcc input.c -o output -lX11
   compile with !g++ --std=c++11 % -L/usr/X11/lib -lX11 -lstdc++
   */

#include "X11_Window.hpp"
#include "XlibWrapper.hpp"
#include "EventDispatcher.hpp"
#include "Settings.hpp"
#include "Command.hpp"
#include "Helper.hpp"
#include "ChangeView.hpp"
#include <iostream>
#include <memory>
#include <thread>
#include <functional>
#include <atomic>

int main(void)
{
  using namespace configuration;

	volatile bool run = true;
  std::list<std::function<void()>> ui_event_queue;
  std::unique_ptr<abstractions::ui::AWindow> x_window(new xlib::X11_Window(views::ViewID::NONE));
  auto* x_window_raw = x_window.get();

  auto xlib_thread_function = [&ui_event_queue, x_window_raw, &run]() {
    XInitThreads();
    xlib::XlibWrapper::self()->create_window(configuration::Settings::get_concrete<geometry::Rectangle>(ConfigID::WINDOW_FRAME),
        configuration::Settings::get_concrete<color::COLOR_SCHEME_TYPE>(ConfigID::WINDOW_COLOR_SCHEME),
        configuration::Settings::get_concrete<unsigned int>(ConfigID::WINDOW_BORDER_WIDTH),
        configuration::Settings::get_concrete<std::string>(ConfigID::WINDOW_NAME).c_str(),
        configuration::Settings::get_concrete<std::string>(ConfigID::WINDOW_FONT_NAME).c_str());

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
        if(command->execute()) {
          commands::Command::put_command_with_result(std::move(command));
        }
      }
    }

    xlib::XlibWrapper::self()->destroy_window();
  };

  std::thread xlib_thread(xlib_thread_function);

  std::this_thread::sleep_for(std::chrono::milliseconds(1u));

  commands::Command::push_xlib_command(new commands::ChangeView(views::ViewID::MENU));

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

  xlib_thread.join();
  std::cout << "GOODBYE!" << std::endl;
  return 0;
}
