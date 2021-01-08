#ifndef SRC_INCLUDE_COLOR_COLOR_HPP
#define SRC_INCLUDE_COLOR_COLOR_HPP

#include <sstream>
#include <map>

namespace color {
  struct Color {
    unsigned char red, green, blue;

    Color() = default;
    Color(const unsigned long& value);
    Color(const std::string& value);
    const unsigned long to_long() const; 
    const std::string to_string() const; 
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
