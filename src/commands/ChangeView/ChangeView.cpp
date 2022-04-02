#include "ChangeView.hpp"
#include "helpers/Helper.hpp"
#include <xlib/XProxy/XProxy.hpp>

namespace commands {

  ChangeView::ChangeView(views::ViewID&& viewID) 
  : viewID(viewID) {
  }

  void ChangeView::execute(xlib::XProxy& proxy) {
    helpers::Helper::SendChangeViewEvent(proxy, viewID);
  }

}

