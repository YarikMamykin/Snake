#include "gtest/gtest.h"
#include "color/ColorPallete.hpp"
#include <vector>
#include <algorithm>

namespace {
  const color::Color red("#ff0000");
  const color::Color green("#00ff00");
  const color::Color blue("#0000ff");
  const color::Color cyan("#00ffff");
  const color::Color white("#ffffff");
}

namespace colors_test {

  using ColorPallete = color::ColorPallete;

TEST(ColorPalleteTest, CreateColorPalleteFromColor) {
  for(const auto& color : { red,green,blue,cyan,white }) {
    ColorPallete color_pallete(color);
    EXPECT_EQ(color, color_pallete.get_current_color());
  }
}

TEST(ColorPalleteTest, IterateColorsInPallete) {
  ColorPallete color_pallete(cyan);
  std::vector<color::Color> colors = { red,green,blue,cyan };

  for(const auto& color : colors) {
    auto found_color = std::find(colors.begin(), colors.end(), color_pallete.get_current_color());
    EXPECT_NE(found_color, colors.end());
    ++color_pallete;
  }

  for(const auto& color : colors) {
    auto found_color = std::find(colors.begin(), colors.end(), color_pallete.get_current_color());
    EXPECT_NE(found_color, colors.end());
    --color_pallete;
  }
}

}
