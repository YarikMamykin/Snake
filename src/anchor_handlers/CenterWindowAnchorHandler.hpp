#pragma once

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





