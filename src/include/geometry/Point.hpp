#ifndef SRC_INCLUDE_GEOMETRY_POINT_HPP
#define SRC_INCLUDE_GEOMETRY_POINT_HPP

namespace geometry {
  struct Point {
    int x,y;

    friend bool operator < (const Point& a, const Point& b) {
      return (a.x < b.x) && (a.y < b.y);
    }

    friend bool operator > (const Point& a, const Point& b) {
      return (a.x > b.x) && (a.y > b.y);
    }
  };
}


#endif /* SRC_INCLUDE_GEOMETRY_POINT_HPP */
