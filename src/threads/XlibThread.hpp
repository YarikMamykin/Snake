#pragma once 

#include <functional>
#include <list>
#include <future>
// #include <mutex>
// #include <condition_variable>

namespace std {
  class mutex;
  class condition_variable;
}

namespace abstractions::ui {
  class AWindow;
}

namespace threads {
  class UI_EventQueue;
}

namespace threads {
  class XlibThread { 

    private:
      std::future<void> m_handler;

    public:
      explicit XlibThread();
      ~XlibThread();

      bool init() const noexcept;

      void run(          
          UI_EventQueue& ui_event_queue, 
          std::mutex& sync_mutex,
          std::shared_ptr<abstractions::ui::AWindow> x_window,
          std::condition_variable& ui_events_available) noexcept;
  };
}

