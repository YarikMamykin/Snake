#include "Food.hpp"
#include "XlibWrapper.hpp"

namespace game_objects {

  Food::Food(color::Color&& background_color, color::Color&& color, geometry::Rectangle&& frame) 
  : background_color(background_color) 
  , color(color) 
  , frame(std::move(frame)) { }

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
