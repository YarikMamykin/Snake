#include "ColorValuePresenter.hpp"

namespace ui {
  ColorValuePresenter::ColorValuePresenter(const color::ColorPallete& value, 
                                           std::unique_ptr<xlib::X11_ColorLabel> color_label) 
  : abstractions::ui::ValuePresenter<color::ColorPallete, xlib::X11_ColorLabel>(std::make_shared<abstractions::ObservableValue<color::ColorPallete>>(value), std::move(color_label)) { 
    update_presenter();
  }
  
  void ColorValuePresenter::update_presenter() { 
    this->presenting_object->set_color(observable_value->get_value().get_current_color());
  }
}
