#pragma once

#include <memory>
#include "abstractions/ui/Object.hpp"

namespace abstractions::ui {

  class AWindow : public Object {
    protected:
      AWindow() : Object() {}
      AWindow(const geometry::Rectangle& frame, const color::COLOR_SCHEME_TYPE& color_scheme) 
        : Object(frame, color_scheme) {}

    public:
      virtual bool closing() const noexcept = 0;
      virtual ~AWindow() {};
  };
}
