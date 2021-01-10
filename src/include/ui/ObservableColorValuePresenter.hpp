#ifndef SRC_INCLUDE_UI_OBSERVABLECOLORVALUEPRESENTER_HPP
#define SRC_INCLUDE_UI_OBSERVABLECOLORVALUEPRESENTER_HPP

#include "ObservableValuePresenter.hpp"
#include "X11_ColorLabel.hpp"

namespace ui {
  class ObservableColorValuePresenter : public abstractions::ui::ObservableValuePresenter<color::ColorPallete, xlib::X11_ColorLabel> {
    public:
      ObservableColorValuePresenter(std::shared_ptr<abstractions::ObservableValue<color::ColorPallete>> value, std::unique_ptr<xlib::X11_ColorLabel> text_label);

      void update_presenter() override;
  };
}


#endif /* SRC_INCLUDE_UI_OBSERVABLECOLORVALUEPRESENTER_HPP */
