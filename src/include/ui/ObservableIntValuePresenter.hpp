#ifndef SRC_INCLUDE_UI_OBSERVABLEINTVALUEPRESENTER_HPP
#define SRC_INCLUDE_UI_OBSERVABLEINTVALUEPRESENTER_HPP

#include "ObservableValuePresenter.hpp"
#include "X11_TextLabel.hpp"

namespace ui {
  class ObservableIntValuePresenter : public abstractions::ui::ObservableValuePresenter<int, xlib::X11_TextLabel> {
    public:
      ObservableIntValuePresenter(std::shared_ptr<abstractions::ObservableValue<int>> value, std::unique_ptr<xlib::X11_TextLabel> text_label);

      void update_presenter() override;
  };
}


#endif /* SRC_INCLUDE_UI_OBSERVABLEINTVALUEPRESENTER_HPP */
