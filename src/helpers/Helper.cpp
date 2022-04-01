#include "Helper.hpp"
#include <xlib/XProxy/XProxy.hpp>

namespace helpers {
  XEvent Helper::ConstructExitApplicationEvent() {
    XEvent event;
    event.xclient.type = ClientMessage; 
    event.xclient.format = 32;
    event.xclient.data.l[0] = events::AdditionalEvents::ExitApplication;
    return event;
  }

  XEvent Helper::ConstructChangeViewEvent(const views::ViewID& viewID) {
    XEvent event;
    event.xclient.type = ClientMessage; 
    event.xclient.format = 32;
    event.xclient.data.l[0] = events::AdditionalEvents::ChangeView;
    event.xclient.data.l[1] = viewID;
    return event;
  }

  void Helper::SendExitApplicationEvent(xlib::XProxy& proxy) {
    auto&& event = helpers::Helper::ConstructExitApplicationEvent();
    proxy.send_client_event(NoEventMask, &event);
  }

  void Helper::SendChangeViewEvent(xlib::XProxy& proxy, const views::ViewID& viewID) {
    auto&& event = helpers::Helper::ConstructChangeViewEvent(viewID);
    proxy.send_client_event(NoEventMask, &event);
  }
}
