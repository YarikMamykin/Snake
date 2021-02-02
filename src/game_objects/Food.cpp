#include "Food.hpp"
#include "XlibWrapper.hpp"

namespace game_objects {

  Food::Food(const color::Color&& background_color, const color::Color&& color, geometry::Rectangle&& frame) 
  : background_color(background_color) 
  , color(color) 
  , frame(std::forward<decltype(frame)>(frame)) { }

  Food::~Food() {
    xlib::XlibWrapper::self()->fill_circle(std::forward<decltype(frame)>(frame), 
                                           std::forward<decltype(background_color)>(background_color));
    xlib::XlibWrapper::self()->flush_buffer();
  }

  void Food::show() {
    xlib::XlibWrapper::self()->fill_circle(std::forward<decltype(frame)>(frame), 
                                           std::forward<decltype(background_color)>(color));
    xlib::XlibWrapper::self()->flush_buffer();
  }
}
