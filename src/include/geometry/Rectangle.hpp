#ifndef SRC_INCLUDE_GEOMETRY_RECTANGLE_HPP
#define SRC_INCLUDE_GEOMETRY_RECTANGLE_HPP

#include "geometry/Point.hpp"
#include "constants/Constants.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <sstream>
#include <array>

namespace geometry {
  /*
   * This structure replaces original XRectangle
   *   as soon as 'x' and 'y' params there are of 'short' type!
   */
  struct Rectangle {
    int x,y;
    unsigned int width, height;

    Rectangle() = default;
    Rectangle(const Rectangle&) = default;
    Rectangle(Rectangle&&) = default;
    Rectangle& operator=(const Rectangle&) = default;

    Rectangle(const int& x, const int& y) : x(x), y(y), width(), height() { }
    Rectangle(const unsigned int& w, const unsigned int& h) : width(w), height(h) { }
    Rectangle(const int& x, const int& y, const unsigned int& w, const unsigned int& h) : x(x), y(y), width(w), height(h) { }

    friend bool operator == (const Rectangle& a, const Rectangle& b) {
      const auto&& a_tl = a.top_left();
      const auto&& b_tl = b.top_left();
      return (a_tl == b_tl) && (a.width == b.width) && (a.height == b.height);
    }

    Point bottom_right() const {
      return { .x = x + width, .y = y + height };
    }

    Point top_right() const {
      return { .x = x + width, .y = y };
    }

    Point bottom_left() const {
      return { .x = x , .y = y + height };
    }

    Point top_left() const {
      return { .x = x, .y = y };
    }

    Point center() const {
      return { .x = width/2 + x, .y = height/2 + y };
    }

    void move(const int& x, const int& y) {
      this->x += x;
      this->y += y;
    }

    void set_position(const int& x, const int& y) {
      this->x = x;
      this->y = y;
    }

    void set_center(const int& x, const int& y) {
      this->x = x - this->width/2;
      this->y = y - this->height/2;
    }

    const std::string to_string() const {
      std::ostringstream rect_data;
      rect_data << "Rectangle:"
        << std::endl
        << "X: " << this->x
        << std::endl
        << "Y: " << this->y
        << std::endl
        << "WIDTH: " << this->width
        << std::endl
        << "HEIGHT: " << this->height
        << std::endl;
      return rect_data.str();
    }

    bool has_point(Point&& p) const {
      const auto&& top_left_p = top_left();
      const auto&& bottom_right_p = bottom_right();
      return p >= top_left_p && bottom_right_p >= p;
    }

    bool belongs_to(const Rectangle& rect) const {
      std::array rectangle_points { top_right(), top_left(), bottom_left(), bottom_right() };
      auto check = [rect](const Point& point) {
        bool&& check1 = point.x >= rect.x;
        bool&& check2 = point.x <= rect.x + rect.width;
        bool&& check3 = point.y >= rect.y; 
        bool&& check4 = point.y <= rect.y + rect.height; 
        return check1 && check2 && check3 && check4;
      };
      return std::all_of(rectangle_points.begin(), rectangle_points.end(), check);
    }

    void rotate(const game_objects::RotationDirection& rotation_direction, Point&& rotation_point) {
      if(rotation_direction == game_objects::RotationDirection::NONE) {
        return;
      }

      std::array points {top_left(), top_right(), bottom_left(), bottom_right()};
      std::for_each(points.begin(), points.end(), [&rotation_direction, &rotation_point](Point& p) -> void { 
          p.rotate(game_objects::RotationDirection(rotation_direction), Point(rotation_point)); 
      });
      auto&& new_top_left = *std::min_element(points.begin(), points.end());
      this->x = new_top_left.x;
      this->y = new_top_left.y;
      std::swap(this->width, this->height);
    }

    bool do_not_cross(const Rectangle& r) const {
      auto&& tl = top_left();
      auto&& br = bottom_right();
      auto&& rtl = r.top_left();
      auto&& rbr = r.bottom_right();

      bool&& this_left_of = tl.x > rbr.x;
      bool&& this_right_of = br.x < rtl.x;
      bool&& this_lower = tl.y > rbr.y;
      bool&& this_upper = br.y < rtl.y;

      return this_left_of || this_right_of || this_lower || this_upper;
    }
  };
}

#endif /* SRC_INCLUDE_GEOMETRY_RECTANGLE_HPP */
