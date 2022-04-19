#pragma once
#include "abstractions/ui/Object.hpp"

namespace abstractions::ui {

  class TextLabel : public Object {
    protected:
      std::string text;

      TextLabel() : Object() {}
      TextLabel(const std::string& text, 
          const geometry::Rectangle& frame, 
          const color::COLOR_SCHEME_TYPE& color_scheme) 
        : Object(frame, color_scheme) 
          , text(text) {}

    public:
      virtual void set_text(const std::string& text) { this->text = text; }
      virtual const std::string get_text() const { return this->text; }

      virtual ~TextLabel() {};
  };
}

