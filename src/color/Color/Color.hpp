#pragma once

#include <bitset>
#include <string_view>

namespace color {

  class Color {
    std::bitset<24> m_self;

    public:

      Color(const Color&) = default;
      Color& operator=(const Color&) = default;
      Color(unsigned long value) noexcept;
      Color(std::string_view value);

      Color() = delete;
      Color(Color&&) = delete;
      Color& operator=(Color&&) = delete;

      operator unsigned long () const; 

      bool operator == (const Color& a) const;

      unsigned char red() const noexcept;
      unsigned char green() const noexcept;
      unsigned char blue() const noexcept;
  };

}
