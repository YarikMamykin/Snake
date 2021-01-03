#ifndef SRC_INCLUDE_UI_COLORVALUEPRESENTER_HPP
#define SRC_INCLUDE_UI_COLORVALUEPRESENTER_HPP

#include "ValuePresenter.hpp"
#include "X11_ColorLabel.hpp"

namespace ui {
  class ColorValuePresenter : public abstractions::ui::ValuePresenter<abstractions::ui::ColorLabel::Color, xlib::X11_ColorLabel> {
    public:
      ColorValuePresenter(const abstractions::ui::ColorLabel::Color& value, std::unique_ptr<xlib::X11_ColorLabel> text_label);

      void update_presenter() override;
  };
}

#endif /* SRC_INCLUDE_UI_COLORVALUEPRESENTER_HPP */
