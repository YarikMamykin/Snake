#ifndef SRC_INCLUDE_UI_ULONGVALUEPRESENTER_HPP
#define SRC_INCLUDE_UI_ULONGVALUEPRESENTER_HPP

#include "ValuePresenter.hpp"
#include "X11_TextLabel.hpp"

namespace ui {
  class UlongValuePresenter : public abstractions::ui::ValuePresenter<unsigned long, xlib::X11_TextLabel> {
    public:
      UlongValuePresenter(const unsigned long& value, std::unique_ptr<xlib::X11_TextLabel> text_label);

      void update_presenter() override;
  };
}
#endif /* SRC_INCLUDE_UI_ULONGVALUEPRESENTER_HPP */
