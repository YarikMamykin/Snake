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

    auto window = std::make_shared<xlib::X11_Window>(views::ViewID::NONE);

    ui_thread.run(window);

    xlib_thread.run(window);
  } 

  ThreadDispatcher::~ThreadDispatcher() = default;
}
