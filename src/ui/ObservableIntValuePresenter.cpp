#include "ObservableIntValuePresenter.hpp"

namespace ui {
  ObservableIntValuePresenter::ObservableIntValuePresenter(std::shared_ptr<abstractions::ObservableValue<int>> value, std::unique_ptr<xlib::X11_TextLabel> text_label) 
  : abstractions::ui::ObservableValuePresenter<int, xlib::X11_TextLabel>(value, std::move(text_label)) { 
    update_presenter();
  }
  
  void ObservableIntValuePresenter::update_presenter() {
    this->presenting_object->set_text(std::to_string(this->observable_value->get_value()));
  }
}
