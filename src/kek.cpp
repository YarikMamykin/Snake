/*
   Simple Xlib application for creating a window and drawing a box in it.
   gcc input.c -o output -lX11
   compile with !g++ --std=c++11 % -L/usr/X11/lib -lX11 -lstdc++
   */

#include "X11_Window.hpp"
#include "X11_Display.hpp"
#include "EventHandler.hpp"
#include "Settings.hpp"
#include <iostream>
#include <memory>

void LaunchApp() {
  using namespace xlib;
  using namespace events;
  XInitThreads();

  std::shared_ptr<interfaces::IWindow> x_window = std::make_shared<X11_Window>(views::ViewID::MENU, settings::Settings::settings().win_sets);
  std::shared_ptr<ui::UI_Object> x_window_as_ui_object = std::dynamic_pointer_cast<ui::UI_Object>(x_window);
  std::shared_ptr<ui::UI_Object> view_as_ui_object = std::dynamic_pointer_cast<ui::UI_Object>(x_window->get_view());
  x_window->show();

  EventHandler ehandler;
  ehandler.add_listener(constants::HandlerKeys::WINDOW, x_window_as_ui_object);
  ehandler.add_listener(constants::HandlerKeys::WINDOW_VIEW, view_as_ui_object);
  ehandler.event_handler_loop(x_window.get());
}

int main(void)
{
  LaunchApp();
  std::cout << "GOODBYE!" << std::endl;
  return 0;
}
