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

  void Helper::SendExitApplicationEvent() {
    auto&& event = helpers::Helper::ConstructExitApplicationEvent();
    xlib::XlibWrapper::self()->send_event(NoEventMask, &event);
  }

  void Helper::SendChangeViewEvent(const views::ViewID& viewID) {
    auto&& event = helpers::Helper::ConstructChangeViewEvent(viewID);
    xlib::XlibWrapper::self()->send_event(NoEventMask, &event);
  }
}
