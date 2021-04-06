#include "ColorValuePresenter.hpp"
#include "Settings.hpp"

namespace ui {
  ColorValuePresenter::ColorValuePresenter(const color::ColorPallete& value, 
                                           std::unique_ptr<xlib::X11_ColorLabel> color_label) 
  : abstractions::ui::ValuePresenter<color::ColorPallete, xlib::X11_ColorLabel>(value, std::move(color_label)) { 
    update_presenter();
  }
  
  void ColorValuePresenter::update_presenter() { 
    this->presenting_object->set_color(this->value.get_current_color());
  }
}
