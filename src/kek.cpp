#include <memory>
#include <functional>
#include <list>
#include "xlib/X11_Window.hpp"
#include "commands/ChangeView.hpp"
#include "threads/XlibThread.hpp"
#include "threads/UI_Thread.hpp"

int main(void)
{
  std::list<std::function<void()>> ui_event_queue;
  std::unique_ptr<abstractions::ui::AWindow> x_window(new xlib::X11_Window(views::ViewID::NONE));
	bool run = true;

  threading::XlibThread xlib_thread(ui_event_queue, x_window.get(), run);
  threading::UI_Thread ui_thread(ui_event_queue, run);

  commands::Command::push_xlib_command(new commands::ChangeView(views::ViewID::MENU));

  return 0;
}
