#pragma once
#include <abstractions/ui/TextLabel.hpp>
#include <string>
#include <color/ColorScheme.hpp>

namespace xlib {
	struct X11_TextLabel : public abstractions::ui::TextLabel {
			X11_TextLabel() = default;
      X11_TextLabel(const std::string& text, 
                    const geometry::Rectangle& frame, 
                    const color::COLOR_SCHEME_TYPE& color_scheme) {}
			~X11_TextLabel() = default;

      void show(bool show_flag) override {}
      void show_frame(bool show_flag) override {}
	};
}
