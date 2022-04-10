#pragma once

#include "geometry/Rectangle.hpp"
#include "color/Color/Color.hpp"
#include "timing/Timer.hpp"

namespace game_objects {
  struct Food final {
    color::Color background_color, color; 
    geometry::Rectangle frame;
    timing::Timer timer;

    public:
    Food(color::Color&& background_color, color::Color&& color, geometry::Rectangle&& frame);
    ~Food();
  };
}
