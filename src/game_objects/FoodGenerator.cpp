#include "game_objects/FoodGenerator.hpp"
#include "geometry/Point.hpp"
#include "color/ColorPallete.hpp"
#include <chrono>

namespace {
    constexpr int weird_number = 123/4*5-70+3;
    constexpr int another_weird_number = 390*2/5+30-2*8/7;
}

namespace game_objects {
  RandomEngine::RandomEngine() {
    algorithm.seed(std::chrono::milliseconds(std::time(nullptr)).count());
  }

  geometry::Point RandomEngine::generate_point(geometry::Rectangle&& region) {
    /*
     * Random Engine should generate coords
     * in some close field around the snake head.
     */
    auto&& generated_number = algorithm();
    int&& x = generated_number ^ weird_number;
    int&& y = generated_number ^ another_weird_number;
    const bool x_in_range = x >= region.x && x <= (region.x + region.width);
    const bool y_in_range = y >= region.y && y <= (region.y + region.height);
    return {x_in_range ? x : region.x, y_in_range ? y : region.y};
  }
}

namespace game_objects {
  FoodGenerator::FoodGenerator(const unsigned int& window_width, const unsigned int& window_height) 
  : window_width(window_width)
  , window_height(window_height)
  , prev_point(geometry::Point{}) {
  }

  Food* FoodGenerator::generate() {
    using namespace configuration;
    auto& background_color = config::get_concrete_ref<color::COLOR_SCHEME_TYPE>(config_id::WINDOW_COLOR_SCHEME).at(color::ColorSchemeID::BackgroundColor);
    auto&& food_color = Settings::get_concrete_ref<color::ColorPallete>(ConfigID::FOOD_COLOR).get_current_color();
    auto&& food_size = Settings::get_concrete_ref<RESTRICTED_UINT>(ConfigID::SNAKE_SIZE).get_restricted_value() * Settings::get_concrete<const unsigned int>(ConfigID::SIZE_MULTIPLIER) + 5u;
    auto&& region = geometry::Rectangle{200,200,window_width - 300u,window_height - 300u};

    geometry::Point&& generated_point{};
    while((generated_point = points_generator.generate_point(std::move(region))) == prev_point);
    prev_point = generated_point;
    auto&& food_frame = geometry::Rectangle{ generated_point.x, generated_point.y, food_size, food_size };

    return new Food(color::Color(background_color), color::Color(food_color), std::move(food_frame));
  }
}
