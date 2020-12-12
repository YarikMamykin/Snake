#include "Helper.hpp"

namespace helpers {
  XEvent Helper::ConstructExitApplicationEvent(const xlib::X11_Window* x_window) {
    XEvent event;
    event.xclient.type = ClientMessage; 
    event.xclient.format = 32;
    event.xclient.window = x_window->window;
    event.xclient.display = x_window->x_display.display;
    event.xclient.data.l[0] = events::AdditionalEvents::ExitApplication;
    return event;
  }

  XEvent Helper::ConstructChangeViewEvent(const xlib::X11_Window* x_window, const views::ViewID& viewID) {
    XEvent event;
    event.xclient.type = ClientMessage; 
    event.xclient.format = 32;
    event.xclient.window = x_window->window;
    event.xclient.display = x_window->x_display.display;
    event.xclient.data.l[0] = events::AdditionalEvents::ChangeView;
    event.xclient.data.l[1] = viewID;
    return event;
  }

  void Helper::SendExitApplicationEvent(const xlib::X11_Window* x_window) {
    auto event = helpers::Helper::ConstructExitApplicationEvent(x_window);
    XSendEvent(x_window->x_display.display, x_window->window, true, NoEventMask, &event);
  }

  void Helper::SendChangeViewEvent(const xlib::X11_Window* x_window, const views::ViewID& viewID) {
    auto event = helpers::Helper::ConstructChangeViewEvent(x_window, viewID);
    XSendEvent(x_window->x_display.display, x_window->window, true, NoEventMask, &event);
  }

}
