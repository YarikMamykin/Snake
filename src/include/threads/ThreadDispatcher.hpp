#ifndef SRC_INCLUDE_THREADS_THREADDISPATCHER_HPP
#define SRC_INCLUDE_THREADS_THREADDISPATCHER_HPP

#include "threads/XlibThread.hpp"
#include "threads/UI_Thread.hpp"
#include <memory>
#include <thread>
#include <functional>

namespace threads {
  class ThreadDispatcher {
    std::list<std::function<void()>> ui_event_queue;
    bool run;
    threads::XlibThread xlib_thread;
    threads::UI_Thread ui_thread;

    public: 
    explicit ThreadDispatcher();
    ~ThreadDispatcher();
  };
}



#endif /* SRC_INCLUDE_THREADS_THREADDISPATCHER_HPP */
