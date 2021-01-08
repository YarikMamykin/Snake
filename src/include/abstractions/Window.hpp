#ifndef SRC_INCLUDE_ABSTRACTIONS_WINDOW_HPP
#define SRC_INCLUDE_ABSTRACTIONS_WINDOW_HPP

#include <memory>
#include <View.hpp>
#include "Object.hpp"

namespace abstractions {
  namespace ui {

    class AWindow : public Object {
      protected:
        AWindow() : Object() {}
        AWindow(const geometry::Rectangle& frame, const color::COLOR_SCHEME_TYPE& color_scheme) 
        : Object(frame, color_scheme) {}
        
      public:
        virtual void expose() = 0;
        virtual void change_view(const int viewID) = 0;
        virtual std::shared_ptr<views::View> get_view() const = 0;

        virtual ~AWindow() {};
    };
  }
}
#endif /* SRC_INCLUDE_ABSTRACTIONS_WINDOW_HPP */
