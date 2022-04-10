#include "UI_EventQueue.hpp"
#include <mutex>

namespace threads {

  std::mutex UI_EventQueue::ui_event_queue_mutex;
  std::condition_variable UI_EventQueue::ui_event_queue_cv;
  std::list<UI_Event> UI_EventQueue::ui_event_queue;

  void UI_EventQueue::push(UI_Event&& event) {
    std::lock_guard<std::mutex> guard(ui_event_queue_mutex);
    ui_event_queue.push_back(std::move(event));
    ui_event_queue_cv.notify_all();
  }

  UI_Event UI_EventQueue::wait_and_pop() {
    std::unique_lock<std::mutex> guard(ui_event_queue_mutex);
    ui_event_queue_cv.wait(guard, [](){ return !ui_event_queue.empty();});

    auto event = ui_event_queue.front();
    ui_event_queue.pop_front();
    return event;
  }
}
