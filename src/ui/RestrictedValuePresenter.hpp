#pragma once

#include "abstractions/values/RestrictedValue.hpp"
#include "abstractions/ui/ValuePresenter.hpp"
#include <xlib/X11_TextLabel/X11_TextLabel.hpp>
#include <memory>

namespace abstractions::ui {
  template<typename RestrictedValueType>
  class RestrictedValuePresenter : public ConfigValuePresenter<abstractions::values::RestrictedValue<RestrictedValueType>, xlib::X11_TextLabel> {
    public:
      RestrictedValuePresenter<RestrictedValueType>(config_id config_value_id, std::unique_ptr<xlib::X11_TextLabel> text_label)
        : ConfigValuePresenter<abstractions::values::RestrictedValue<RestrictedValueType>, xlib::X11_TextLabel>(config_value_id, std::move(text_label)) { 
          update_presenter();
        }

      void update_presenter() override {
        this->presenter->set_text(std::to_string(this->get_value().get_restricted_value()));
      }
  };
}



