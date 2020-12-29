#ifndef SRC_INCLUDE_ABSTRACTIONS_WINDOWANCHORHANDLER_HPP
#define SRC_INCLUDE_ABSTRACTIONS_WINDOWANCHORHANDLER_HPP

#include "Constants.hpp"
#include "X11_Window.hpp"
#include "Rectangle.hpp"

namespace ui {

  /*
   * Positions Object to the LEFT,RIGHT or CENTER 
   * of Window
   */
  template <class Object, AnchorType anchor_type = AnchorType::CENTER>
    class WindowAnchorHandler {
      public:
        WindowAnchorHandler(Object* object, xlib::X11_Window* parent_window) {
          switch(anchor_type) {
            case AnchorType::CENTER:           
              {
                auto&& window_center = get_window_center(parent_window);
                object->set_center(window_center.x, window_center.y);
                break;
              }
          }
        }

      private:
        geometry::Point get_window_center(xlib::X11_Window* parent_window) {
          parent_window->update_window_frame();
          return { .x = parent_window->get_width()/2, .y = parent_window->get_height()/2 };
        }
    };
}



#endif /* SRC_INCLUDE_ABSTRACTIONS_WINDOWANCHORHANDLER_HPP */
