#pragma once

#include <sstream>
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

}
