#include "ColorValuePresenter.hpp"

namespace ui {
  ColorValuePresenter::ColorValuePresenter(const abstractions::ui::ColorLabel::Color& value, 
                                           std::unique_ptr<xlib::X11_ColorLabel> color_label) 
  : abstractions::ui::ValuePresenter<abstractions::ui::ColorLabel::Color, xlib::X11_ColorLabel>(value, std::move(color_label)) { 
    update_presenter();
  }
  
  void ColorValuePresenter::update_presenter() {
    this->presenting_object->set_color(value);
  }
}
