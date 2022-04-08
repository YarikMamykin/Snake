#pragma once

#include <list>
#include <mutex>
#include "UI_Event.hpp"

namespace threads {
  class UI_EventQueue {

    private:
      static std::mutex ui_event_queue_mutex;
      static std::list<UI_Event> ui_event_queue;

    public:
      static void push(UI_Event&& event);
      static void pop();
  };
}
