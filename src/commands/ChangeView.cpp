#include "ChangeView.hpp"
#include "Helper.hpp"

namespace commands {

  ChangeView::ChangeView(views::ViewID&& viewID) 
  : viewID(viewID) {
  }

  DoSaveResult ChangeView::execute() {
    helpers::Helper::SendChangeViewEvent(viewID);
    return DoSaveResult::NO;
  }

  /* constexpr */ CommandID ChangeView::get_id() const {
    return CommandID::ChangeView;
  }
}

