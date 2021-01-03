#include "UlongValuePresenter.hpp"

namespace ui {
  UlongValuePresenter::UlongValuePresenter(const unsigned long& value, std::unique_ptr<xlib::X11_TextLabel> text_label) 
  : abstractions::ui::ValuePresenter<unsigned long, xlib::X11_TextLabel>(value, std::move(text_label)) { 
    update_presenter();
  }
  
  void UlongValuePresenter::update_presenter() {
    this->presenting_object->set_text(std::to_string(value));
  }
}
