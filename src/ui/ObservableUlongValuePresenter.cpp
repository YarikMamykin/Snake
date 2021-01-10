#include "ObservableUlongValuePresenter.hpp"

namespace ui {
  ObservableUlongValuePresenter::ObservableUlongValuePresenter(std::shared_ptr<abstractions::ObservableValue<unsigned long>> value, std::unique_ptr<xlib::X11_TextLabel> text_label) 
  : abstractions::ui::ObservableValuePresenter<unsigned long, xlib::X11_TextLabel>(value, std::move(text_label)) { 
    update_presenter();
  }
  
  void ObservableUlongValuePresenter::update_presenter() {
    this->presenting_object->set_text(std::to_string(value));
  }
}
