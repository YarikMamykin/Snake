#include "Helper.hpp"
#include "XlibWrapper.hpp"

namespace helpers {
  XEvent Helper::ConstructExitApplicationEvent(const xlib::X11_Window* x_window) {
    XEvent event;
    event.xclient.type = ClientMessage; 
    event.xclient.format = 32;
    event.xclient.window = xlib::XlibWrapper::self()->window;
    event.xclient.display = xlib::XlibWrapper::self()->display;
    event.xclient.data.l[0] = events::AdditionalEvents::ExitApplication;
    return event;
  }

  XEvent Helper::ConstructChangeViewEvent(const xlib::X11_Window* x_window, const views::ViewID& viewID) {
    XEvent event;
    event.xclient.type = ClientMessage; 
    event.xclient.format = 32;
    event.xclient.window = xlib::XlibWrapper::self()->window;
    event.xclient.display = xlib::XlibWrapper::self()->display;
    event.xclient.data.l[0] = events::AdditionalEvents::ChangeView;
    event.xclient.data.l[1] = viewID;
    return event;
  }

  XEvent Helper::ConstructResubscribeViewEvent(const xlib::X11_Window* x_window) {
    XEvent event;
    event.xclient.type = ClientMessage; 
    event.xclient.format = 32;
    event.xclient.window = xlib::XlibWrapper::self()->window;
    event.xclient.display = xlib::XlibWrapper::self()->display;
    event.xclient.data.l[0] = events::AdditionalEvents::ResubscribeView;
    return event;
  }

  void Helper::SendExitApplicationEvent(const xlib::X11_Window* x_window) {
    auto event = helpers::Helper::ConstructExitApplicationEvent(x_window);
    XSendEvent(xlib::XlibWrapper::self()->display, xlib::XlibWrapper::self()->window, true, NoEventMask, &event);
  }

  void Helper::SendChangeViewEvent(const xlib::X11_Window* x_window, const views::ViewID& viewID) {
    auto event = helpers::Helper::ConstructChangeViewEvent(x_window, viewID);
    XSendEvent(xlib::XlibWrapper::self()->display, xlib::XlibWrapper::self()->window, true, NoEventMask, &event);
  }

  void Helper::SendResubscribeViewEvent(const xlib::X11_Window* x_window) {
    auto event = helpers::Helper::ConstructResubscribeViewEvent(x_window);
    XSendEvent(xlib::XlibWrapper::self()->display, xlib::XlibWrapper::self()->window, true, NoEventMask, &event);
  }
}
