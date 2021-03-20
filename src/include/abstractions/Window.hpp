#ifndef SRC_INCLUDE_ABSTRACTIONS_WINDOW_HPP
#define SRC_INCLUDE_ABSTRACTIONS_WINDOW_HPP

#include <memory>
#include "Object.hpp"

namespace abstractions::ui {

  class AWindow : public Object {
    protected:
      AWindow() : Object() {}
      AWindow(const geometry::Rectangle& frame, const color::COLOR_SCHEME_TYPE& color_scheme) 
        : Object(frame, color_scheme) {}

    public:
      virtual ~AWindow() {};
  };
}
#endif /* SRC_INCLUDE_ABSTRACTIONS_WINDOW_HPP */
