#pragma once
#include "abstractions/ui/ValuePresenter.hpp"
#include "xlib/X11_ColorLabel/X11_ColorLabel.hpp"

namespace ui {
  class ColorValuePresenter : public abstractions::ui::ConfigValuePresenter<color::ColorPallete, xlib::X11_ColorLabel> {
    public:
      ColorValuePresenter(config_id config_value_id, std::unique_ptr<xlib::X11_ColorLabel> text_label);

      void update_presenter() override;
  };
}


