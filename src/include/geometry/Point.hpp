#ifndef SRC_INCLUDE_GEOMETRY_POINT_HPP
#define SRC_INCLUDE_GEOMETRY_POINT_HPP

#include <string>
#include <sstream>

namespace geometry {
  struct Point {
    int x,y;

    friend bool operator < (const Point& a, const Point& b) {
      return (a.x < b.x) && (a.y < b.y);
    }

    friend bool operator > (const Point& a, const Point& b) {
      return (a.x > b.x) && (a.y > b.y);
    }

    friend bool operator == (const Point& a, const Point& b) {
      return (a.x == b.x) && (a.y == b.y);
    }

    friend bool operator >= (const Point& a, const Point& b) {
      bool equal = a == b;
      bool greater = a > b;
      return equal || greater;
    }

    const std::string to_string() const {
      std::ostringstream point_data;
      point_data << "Point(" << this->x << ":" << this->y << ")" << std::endl;
      return point_data.str();
    }
  };
}


#endif /* SRC_INCLUDE_GEOMETRY_POINT_HPP */
