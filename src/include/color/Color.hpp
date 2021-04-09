#ifndef SRC_INCLUDE_COLOR_COLOR_HPP
#define SRC_INCLUDE_COLOR_COLOR_HPP

#include <sstream>
#include <map>
#include <cstddef>

namespace color {
  struct Color {
    std::byte red, green, blue;

    Color() = default;
    Color(const Color&) = default;
    Color(Color&&) = default;
    Color& operator=(const Color&) = default;
    Color(const unsigned long& value);
    Color(const char* value);
    Color(const std::string& value);
    operator unsigned long () const; 
    operator std::string() const; 
    bool operator == (const Color& a) const;
  };

  enum class ColorSchemeID : unsigned char { 
    BackgroundColor,
    TextColor,
    FrameColor,
    FontColor
  };

  typedef std::map<ColorSchemeID, Color> COLOR_SCHEME_TYPE;
}
#endif /* SRC_INCLUDE_COLOR_COLOR_HPP */
