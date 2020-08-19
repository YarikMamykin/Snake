#ifndef SRC_INCLUDE_GEOMETRY_RECTANGLE_HPP
#define SRC_INCLUDE_GEOMETRY_RECTANGLE_HPP

namespace geometry {
  /*
   * This structure replaces original XRectangle
   *   as soon as 'x' and 'y' params there are of 'short' type!
   */
  struct Rectangle {
    int x,y;
    unsigned int width, height;
  };
}
#endif /* SRC_INCLUDE_GEOMETRY_RECTANGLE_HPP */
