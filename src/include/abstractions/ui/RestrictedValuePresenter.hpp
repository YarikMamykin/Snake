#ifndef SRC_INCLUDE_ABSTRACTIONS_UI_RESTRICTEDVALUEPRESENTER_HPP
#define SRC_INCLUDE_ABSTRACTIONS_UI_RESTRICTEDVALUEPRESENTER_HPP

#include "abstractions/ui/RestrictedValue.hpp"
#include "abstractions/ui/ValuePresenter.hpp"
#include "xlib/X11_TextLabel.hpp"
#include <memory>

namespace abstractions::ui {
  template<typename RestrictedValueType>
  class RestrictedValuePresenter : public ConfigValuePresenter<abstractions::RestrictedValue<RestrictedValueType>, xlib::X11_TextLabel> {
    public:
      RestrictedValuePresenter<RestrictedValueType>(config_id config_value_id, std::unique_ptr<xlib::X11_TextLabel> text_label)
        : ConfigValuePresenter<abstractions::RestrictedValue<RestrictedValueType>, xlib::X11_TextLabel>(config_value_id, std::move(text_label)) { 
          update_presenter();
        }

      void update_presenter() override {
        this->presenter->set_text(std::to_string(this->get_value().get_restricted_value()));
      }
  };
}



#endif /* SRC_INCLUDE_ABSTRACTIONS_UI_RESTRICTEDVALUEPRESENTER_HPP */
