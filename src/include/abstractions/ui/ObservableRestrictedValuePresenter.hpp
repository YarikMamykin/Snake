#ifndef SRC_INCLUDE_ABSTRACTIONS_OBSERVABLERESTRICTEDVALUEPRESENTER_HPP
#define SRC_INCLUDE_ABSTRACTIONS_OBSERVABLERESTRICTEDVALUEPRESENTER_HPP

#include "RestrictedValue.hpp"
#include "ObservableValuePresenter.hpp"
#include "X11_TextLabel.hpp"
#include <memory>

namespace ui {
  template<typename RestrictedValueType>
  class ObservableRestrictedValuePresenter : public abstractions::ui::ObservableValuePresenter<abstractions::RestrictedValue<RestrictedValueType>, xlib::X11_TextLabel> {
    public:
      ObservableRestrictedValuePresenter<RestrictedValueType>(std::shared_ptr<abstractions::ObservableValue<abstractions::RestrictedValue<RestrictedValueType>>> value, std::unique_ptr<xlib::X11_TextLabel> text_label)
        : abstractions::ui::ObservableValuePresenter<abstractions::RestrictedValue<RestrictedValueType>, xlib::X11_TextLabel>(value, std::move(text_label)) { 
          update_presenter();
        }

      void update_presenter() override {
        this->presenting_object->set_text(std::to_string(this->observable_value->get_value().get_restricted_value()));
      }
  };
}

#endif /* SRC_INCLUDE_ABSTRACTIONS_OBSERVABLERESTRICTEDVALUEPRESENTER_HPP */
