#ifndef SRC_INCLUDE_ANCHOR_HANDLERS_CENTERWINDOWANCHORHANDLER_HPP
#define SRC_INCLUDE_ANCHOR_HANDLERS_CENTERWINDOWANCHORHANDLER_HPP

#include "abstractions/ui/Window.hpp"
#include "geometry/Point.hpp"

namespace ui {

  /*
   * Positions Object to the LEFT,RIGHT or CENTER of Window
   */

  class CenterWindowAnchorHandler {
    public:
      explicit CenterWindowAnchorHandler(abstractions::ui::Object* object);
    private:
      geometry::Point get_window_center();
  };
}





#endif /* SRC_INCLUDE_ANCHOR_HANDLERS_CENTERWINDOWANCHORHANDLER_HPP */
