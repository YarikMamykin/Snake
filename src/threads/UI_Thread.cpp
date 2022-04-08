#include "threads/UI_Thread.hpp"
#include "configuration/Settings.hpp"
#include "commands/ChangeView/ChangeView.hpp"
#include "UI_EventQueue.hpp"
#include <abstractions/ui/Window.hpp>
#include <mutex>
#include <condition_variable>

namespace threads {

  UI_Thread::UI_Thread() = default;
  UI_Thread::~UI_Thread() = default;

      
  void UI_Thread::run(
      UI_EventQueue& ui_event_queue, 
      std::mutex& sync_mutex, 
      std::shared_ptr<abstractions::ui::AWindow> x_window,
      std::condition_variable& ui_events_available) noexcept {

    auto runner = [ &ui_event_queue, x_window, &ui_events_available ]() mutable noexcept {

      commands::Command::push_xlib_command(std::make_unique<commands::ChangeView>(views::ViewID::MENU));
      while(true);

      // while(!x_window->closing()) {
        // ui_event_queue.pop();
      // }
    };

    m_handler = std::async(std::launch::deferred, runner);
    m_handler.wait();
  }

}
