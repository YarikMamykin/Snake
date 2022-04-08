#include "threads/ThreadDispatcher.hpp"
#include "UI_EventQueue.hpp"
#include <memory>
#include <thread>
#include <functional>
#include <list>
#include <atomic>
#include <iostream>
#include <xlib/X11_Window/X11_Window.hpp>
#include <events/EventDispatcher/EventDispatcher.hpp>

namespace threads {
  ThreadDispatcher::ThreadDispatcher() 
  : xlib_thread() 
  , ui_thread() { 

    if(!xlib_thread.init()) 
      return;

    std::atomic_bool need_to_run;

    UI_EventQueue ui_event_queue;
    std::mutex sync_mutex;
    std::condition_variable ui_events_available;

    auto window = std::make_shared<xlib::X11_Window>(views::ViewID::NONE);

    xlib_thread.run(ui_event_queue, sync_mutex, window, ui_events_available);

    // ui_thread.run(ui_event_queue, sync_mutex, window, ui_events_available);
  } 

  ThreadDispatcher::~ThreadDispatcher() = default;
}
