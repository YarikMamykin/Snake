#pragma once
#include <gmock/gmock.h>
#include <string>
#include <geometry/Rectangle.hpp>
#include <color/ColorPallete/ColorPallete.hpp>
#include <color/ColorScheme.hpp>
#include <abstractions/ui/Object.hpp>

namespace xlib {
  class X11_ColorizedTextLabel : public abstractions::ui::Object {

    public:
      X11_ColorizedTextLabel() = default;
      X11_ColorizedTextLabel(const std::string& text, 
                               const geometry::Rectangle& frame, 
                               const color::COLOR_SCHEME_TYPE& color_scheme, 
															 color::ColorPallete&& char_color_sequence) {}

      virtual ~X11_ColorizedTextLabel() = default;

      MOCK_METHOD(void, shift_colors, ());
      MOCK_METHOD(void, show, (bool), (override));
      MOCK_METHOD(void, show_frame, (bool), (override));
      MOCK_METHOD(void, set_center, (geometry::Point&&), (override));
  };
}
