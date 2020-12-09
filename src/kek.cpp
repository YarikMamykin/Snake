/*
   Simple Xlib application for creating a window and drawing a box in it.
   gcc input.c -o output -lX11
   compile with !g++ --std=c++11 % -L/usr/X11/lib -lX11 -lstdc++
   */

#include "X11_Window.hpp"
#include "X11_Display.hpp"
#include "EventHandler.hpp"
#include "Settings.hpp"
#include <X11/Xlib.h>
#include <iostream>
#include <memory>

void LaunchApp() {
  using namespace xlib;
  using namespace events;
  XInitThreads();
  X11_Display x_display;

  auto x_window = std::make_shared<X11_Window>(x_display, 
      DefaultScreen(x_display.display), 
      views::ViewID::MENU, 
      settings::Settings::settings().win_sets);
  x_window->show();

  EventHandler ehandler;
  ehandler.add_mouse_motion_listener(constants::HandlerKeys::WINDOW, x_window);
  ehandler.add_mouse_motion_listener(constants::HandlerKeys::WINDOW_VIEW, x_window->view);
  ehandler.add_mouse_button_press_listener(constants::HandlerKeys::WINDOW_VIEW, x_window->view);
  ehandler.add_key_press_listener(constants::HandlerKeys::WINDOW_VIEW, x_window->view);
  ehandler.event_handler_loop(*x_window);
}

int main(void)
{
  LaunchApp();
  std::cout << "GOODBYE!" << std::endl;
  return 0;
}
