#ifndef SRC_INCLUDE_ABSTRACTIONS_IWINDOW_HPP
#define SRC_INCLUDE_ABSTRACTIONS_IWINDOW_HPP

#include <memory>
#include <View.hpp>

namespace interfaces {
  class IWindow {
    public:
      virtual void show() const = 0;
      virtual void expose() = 0;
      virtual const int get_x() const = 0;
      virtual const int get_y() const = 0;
      virtual const unsigned int get_width() const = 0;
      virtual const unsigned int get_height() const = 0;
      virtual void change_view(const int viewID) = 0;
      virtual std::shared_ptr<views::View> get_view() const = 0;

      virtual ~IWindow() {};
  };
}
#endif /* SRC_INCLUDE_ABSTRACTIONS_IWINDOW_HPP */
