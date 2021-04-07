#include "ColorValuePresenter.hpp"
#include "Settings.hpp"

namespace ui {
  ColorValuePresenter::ColorValuePresenter(config_id config_value_id, 
                                           std::unique_ptr<xlib::X11_ColorLabel> color_label) 
  : abstractions::ui::ConfigValuePresenter<color::ColorPallete, xlib::X11_ColorLabel>(config_value_id, std::move(color_label)) { 
    update_presenter();
  }
  
  void ColorValuePresenter::update_presenter() { 
    this->presenter->set_color(this->get_value().get_current_color());
  }
}
