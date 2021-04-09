#include "commands/ChangeView.hpp"
#include "helpers/Helper.hpp"

namespace commands {

  ChangeView::ChangeView(views::ViewID&& viewID) 
  : viewID(viewID) {
  }

  void ChangeView::execute() {
    helpers::Helper::SendChangeViewEvent(viewID);
  }

}

