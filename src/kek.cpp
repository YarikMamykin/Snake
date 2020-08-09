/*
   Simple Xlib application for creating a window and drawing a box in it.
   gcc input.c -o output -lX11
   compile with !g++ --std=c++11 % -L/usr/X11/lib -lX11 -lstdc++
   */

#include "X11_Window.hpp"
#include "X11_Display.hpp"
#include "EventHandler.hpp"
#include <iostream>


void LaunchApp() {
  using namespace xlib;
  using namespace events;
  X11_Display x_display;

  X11_Window x_window(x_display, 
      DefaultScreen(x_display.display), 
      views::ViewID::MENU,
      { .x = 10,
      .y = 10,
      .w = 200U,
      .h = 200U,
      .border_width = 1U,
      .border_color = (255L << 16),
      .backgnd_color = (0L),
      .font_color = (255L << 8),
      .name = "Snake",
      .font_name = "*-courier-*-24-*"
      });
  EventHandler ehandler(x_display, x_window);

  x_window.show();
  ehandler.event_handler_loop();
}

int main(void)
{
  LaunchApp();
  std::cout << "GOODBYE!" << std::endl;
  return 0;
}
