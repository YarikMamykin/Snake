#ifndef SRC_INCLUDE_THREADING_UI_THREAD_HPP
#define SRC_INCLUDE_THREADING_UI_THREAD_HPP

#include <functional>
#include <thread>
#include <list>

namespace threading {
  class UI_Thread { 
    private:
      std::thread ui_thread;
    public:
      explicit UI_Thread(std::list<std::function<void()>>& ui_event_queue, bool& run);
      ~UI_Thread();
  };
}


#endif /* SRC_INCLUDE_THREADING_UI_THREAD_HPP */
