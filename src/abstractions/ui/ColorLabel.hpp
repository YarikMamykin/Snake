#pragma once
#include "abstractions/ui/Object.hpp"
#include "color/ColorPallete/ColorPallete.hpp"

namespace abstractions::ui {
  class ColorLabel : public Object {
    public:
      ColorLabel() : Object() {}
      ColorLabel(const color::ColorPallete& color_pallete,
          const geometry::Rectangle& frame, 
          const color::COLOR_SCHEME_TYPE& color_scheme) 
        : Object(frame, color_scheme) 
          , color_pallete(color_pallete) {}

      ColorLabel(const color::Color& color,
          const geometry::Rectangle& frame, 
          const color::COLOR_SCHEME_TYPE& color_scheme) 
        : Object(frame, color_scheme) 
          , color_pallete(color) {}

      virtual void set_color(const color::Color& color) { this->color_pallete.set_color(color); }
      virtual void set_color_pallete(const color::ColorPallete& color_pallete) { this->color_pallete = color_pallete; }
      virtual const color::Color get_color() const { return this->color_pallete.current_color(); }

      virtual ~ColorLabel() {};

    protected:
      color::ColorPallete color_pallete;
  };
}


