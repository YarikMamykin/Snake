#include "ObservableColorValuePresenter.hpp"
#include "Settings.hpp"

namespace ui {
  ObservableColorValuePresenter::ObservableColorValuePresenter(std::shared_ptr<abstractions::ObservableValue<color::ColorPallete>> value, 
                                                               std::unique_ptr<xlib::X11_ColorLabel> color_label) 
  : abstractions::ui::ObservableValuePresenter<color::ColorPallete, xlib::X11_ColorLabel>(value, std::move(color_label)) { 
    update_presenter();
  }
  
  void ObservableColorValuePresenter::update_presenter() { 
    this->presenting_object->set_color(this->observable_value->get_value().get_current_color());
  }
}
