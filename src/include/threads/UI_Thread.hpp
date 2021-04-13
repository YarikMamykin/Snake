#ifndef SRC_INCLUDE_THREADS_UI_THREAD_HPP
#define SRC_INCLUDE_THREADS_UI_THREAD_HPP
#include <functional>
#include <future>
#include <list>

namespace threading {
  class UI_Thread { 
    private:
      std::future<void> ui_thread;
      bool& run;

    public:
      explicit UI_Thread(std::list<std::function<void()>>& ui_event_queue, bool& run);
      ~UI_Thread();
  };
}



#endif /* SRC_INCLUDE_THREADS_UI_THREAD_HPP */
