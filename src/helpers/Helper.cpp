#include "Helper.hpp"
#include "XlibWrapper.hpp"

namespace helpers {
  XEvent Helper::ConstructExitApplicationEvent() {
    XEvent event;
    event.xclient.type = ClientMessage; 
    event.xclient.format = 32;
    event.xclient.window = xlib::XlibWrapper::self()->window;
    event.xclient.display = xlib::XlibWrapper::self()->display;
    event.xclient.data.l[0] = events::AdditionalEvents::ExitApplication;
    return event;
  }

  XEvent Helper::ConstructChangeViewEvent(const views::ViewID& viewID) {
    XEvent event;
    event.xclient.type = ClientMessage; 
    event.xclient.format = 32;
    event.xclient.window = xlib::XlibWrapper::self()->window;
    event.xclient.display = xlib::XlibWrapper::self()->display;
    event.xclient.data.l[0] = events::AdditionalEvents::ChangeView;
    event.xclient.data.l[1] = viewID;
    return event;
  }

  XEvent Helper::ConstructResubscribeViewEvent() {
    XEvent event;
    event.xclient.type = ClientMessage; 
    event.xclient.format = 32;
    event.xclient.window = xlib::XlibWrapper::self()->window;
    event.xclient.display = xlib::XlibWrapper::self()->display;
    event.xclient.data.l[0] = events::AdditionalEvents::ResubscribeView;
    return event;
  }

  void Helper::SendExitApplicationEvent() {
    auto event = helpers::Helper::ConstructExitApplicationEvent();
    XSendEvent(xlib::XlibWrapper::self()->display, xlib::XlibWrapper::self()->window, true, NoEventMask, &event);
  }

  void Helper::SendChangeViewEvent(const views::ViewID& viewID) {
    auto event = helpers::Helper::ConstructChangeViewEvent(viewID);
    XSendEvent(xlib::XlibWrapper::self()->display, xlib::XlibWrapper::self()->window, true, NoEventMask, &event);
  }

  void Helper::SendResubscribeViewEvent() {
    auto event = helpers::Helper::ConstructResubscribeViewEvent();
    XSendEvent(xlib::XlibWrapper::self()->display, xlib::XlibWrapper::self()->window, true, NoEventMask, &event);
  }
}
