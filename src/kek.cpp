/*
   Simple Xlib application for creating a window and drawing a box in it.
   gcc input.c -o output -lX11
   compile with !g++ --std=c++11 % -L/usr/X11/lib -lX11 -lstdc++
   */

#include <memory>
#include <thread>
#include <functional>
#include <list>
#include "Window.hpp"
#include "X11_Window.hpp"
#include "ChangeView.hpp"
#include "XlibThread.hpp"
#include "UI_Thread.hpp"

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
