#ifndef SRC_INCLUDE_UI_OBSERVABLEULONGVALUEPRESENTER_HPP
#define SRC_INCLUDE_UI_OBSERVABLEULONGVALUEPRESENTER_HPP

#include "ObservableValuePresenter.hpp"
#include "X11_TextLabel.hpp"

namespace ui {
  class ObservableUlongValuePresenter : public abstractions::ui::ObservableValuePresenter<unsigned long, xlib::X11_TextLabel> {
    public:
      ObservableUlongValuePresenter(std::shared_ptr<abstractions::ObservableValue<unsigned long>> value, std::unique_ptr<xlib::X11_TextLabel> text_label);

      void update_presenter() override;
  };
}

#endif /* SRC_INCLUDE_UI_OBSERVABLEULONGVALUEPRESENTER_HPP */
