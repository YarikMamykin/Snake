#include "ChangeView.hpp"
#include "Helper.hpp"

namespace commands {

  ChangeView::ChangeView(views::ViewID&& viewID) 
  : viewID(viewID) {
  }

  void ChangeView::execute() {
    helpers::Helper::SendChangeViewEvent(viewID);
  }

}

