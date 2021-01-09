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
    // abstractions::ObservableValueContainerWrapper::to_concrete_value<color::Color>(configuration::Settings::get(configuration::ConfigID::SNAKE_COLOR))->change_value(observable_value->get_value().get_current_color());
  }
}
