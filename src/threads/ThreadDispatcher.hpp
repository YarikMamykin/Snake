#pragma once

#include "threads/XlibThread.hpp"
#include "threads/UI_Thread.hpp"

namespace threads {
  class ThreadDispatcher {

    threads::XlibThread xlib_thread;
    threads::UI_Thread ui_thread;

    public: 
      explicit ThreadDispatcher();
      ~ThreadDispatcher();
  };
}
