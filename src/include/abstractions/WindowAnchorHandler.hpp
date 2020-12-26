#ifndef SRC_INCLUDE_ABSTRACTIONS_WINDOWANCHORHANDLER_HPP
#define SRC_INCLUDE_ABSTRACTIONS_WINDOWANCHORHANDLER_HPP

#include "Constants.hpp"
#include "Window.hpp"
#include "Rectangle.hpp"

namespace ui {

  /*
   * Positions Object to the LEFT,RIGHT or CENTER 
   * of Window
   */
  template <class Object, AnchorType anchor_type = AnchorType::CENTER>
    class WindowAnchorHandler {
      public:
        WindowAnchorHandler(Object* object, abstractions::ui::AWindow* parent_window) {
          auto&& window_center = get_window_center(parent_window);
          auto&& object_width = object->get_width();
          auto&& object_height = object->get_height();
          object->set_position(window_center.x - object_width/2, window_center.y - object_height/2);
        }

      private:
        geometry::Point get_window_center(abstractions::ui::AWindow* parent_window) {
          return { .x = parent_window->get_width()/2, .y = parent_window->get_height()/2 };
        }
    };
}



#endif /* SRC_INCLUDE_ABSTRACTIONS_WINDOWANCHORHANDLER_HPP */
