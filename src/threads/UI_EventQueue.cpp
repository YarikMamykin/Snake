#include "UI_EventQueue.hpp"
#include <mutex>

namespace threads {

  std::mutex UI_EventQueue::ui_event_queue_mutex;
  std::list<UI_Event> UI_EventQueue::ui_event_queue;

  void UI_EventQueue::push(UI_Event&& event) {
    std::lock_guard<std::mutex> guard(ui_event_queue_mutex);
    ui_event_queue.push_back(std::move(event));
  }

  void UI_EventQueue::pop() {
    std::lock_guard<std::mutex> guard(ui_event_queue_mutex);

    if(ui_event_queue.empty())
      return;

    ui_event_queue.front()();
    ui_event_queue.pop_front();
  }
}
