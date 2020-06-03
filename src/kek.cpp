/*
    Simple Xlib application for creating a window and drawing a box in it.
    gcc input.c -o output -lX11
    compile with !g++ --std=c++11 % -L/usr/X11/lib -lX11 -lstdc++
*/
 
#include "X11_Window.hpp"
#include "X11_Display.hpp"

using namespace xlib;

struct EventHandler {
  X11_Window& x_window;
  X11_Display& x_display;
  XEvent event;

  EventHandler(X11_Display& x_display, X11_Window& x_window)
  : x_display(x_display) 
  , x_window(x_window) {
    // select kind of events we are interested in
    XSelectInput(x_display.display, x_window.window, ExposureMask | KeyPressMask);
  }

  void event_handler_loop() {
    // event loop
    for (;;) {
        XNextEvent(x_display.display, &event);

        // draw or redraw the window
        if (event.type == Expose)
        {
          x_window.expose();
        }
        // exit on key press
        if (event.type == KeyPress)
            break;
    }
  }
};

void LaunchApp() {
  X11_Display x_display;
  X11_Window x_window(x_display, DefaultScreen(x_display.display));
  EventHandler ehandler(x_display, x_window);
  
  x_window.show();
  ehandler.event_handler_loop();
}
 
int main(void)
{
    LaunchApp();
    return 0;
}
