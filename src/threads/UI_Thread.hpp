#pragma once 

#include <functional>
#include <future>
#include <list>

namespace abstractions::ui {
  class AWindow;
}

namespace threads {
  class UI_EventQueue;
}

namespace threads {

  class UI_Thread { 

    private:
      std::future<void> m_handler;

    public:
      explicit UI_Thread();
      ~UI_Thread();

      void run(
          UI_EventQueue& ui_event_queue, 
          std::mutex& sync_mutex,
          std::shared_ptr<abstractions::ui::AWindow> x_window,
          std::condition_variable& ui_events_available) noexcept;
  };
}
