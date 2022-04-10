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

      
  void UI_Thread::run(std::shared_ptr<abstractions::ui::AWindow> x_window) noexcept {

    auto runner = [ x_window ]() mutable noexcept {

      commands::Command::push_xlib_command(std::make_unique<commands::ChangeView>(views::ViewID::MENU));

      while(!x_window->closing()) {
        auto event = UI_EventQueue::wait_and_pop();
        event();
      }
    };

    m_handler = std::async(std::launch::async, runner);
  }

}
