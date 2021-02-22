#include "FoodGenerator.hpp"
#include "Point.hpp"
#include "ColorPallete.hpp"

namespace {
    constexpr int weird_number = 123/4*5-70+3;
    constexpr int another_weird_number = 390*2/5+30-2*8/7;
}

namespace game_objects {
  RandomEngine::RandomEngine(std::list<unsigned int>&& seed_sequence) {
    std::seed_seq sequence(seed_sequence.begin(), seed_sequence.end());
    algorithm.seed(sequence);
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
  FoodGenerator::FoodGenerator() 
  : points_generator(configuration::Settings::get_concrete<configuration::RANDOM_ENGINE_SEED_SEQUENCE_TYPE>(configuration::ConfigID::RANDOM_ENGINE_SEED_SEQUENCE)) 
  , prev_point(geometry::Point{}) {
  }

  Food* FoodGenerator::generate(xlib::X11_Window* x_window) {
    auto&& window_width = x_window->get_width();
    auto&& window_height = x_window->get_height();
    auto& background_color = x_window->get_color_scheme().at(color::ColorSchemeID::BackgroundColor);
    auto&& food_color = configuration::Settings::get_concrete<color::ColorPallete>(configuration::ConfigID::FOOD_COLOR).get_current_color();
    auto&& food_size = configuration::Settings::get_concrete<configuration::RESTRICTED_UINT>(configuration::ConfigID::SNAKE_SIZE).get_restricted_value() * 15u + 5u;
    auto&& region = geometry::Rectangle{200,200,x_window->get_width() - 300u,x_window->get_height() - 300u};

    geometry::Point&& generated_point{};
    while((generated_point = points_generator.generate_point(std::move(region))) == prev_point);
    prev_point = generated_point;
    auto&& food_frame = geometry::Rectangle{ generated_point.x, generated_point.y, food_size, food_size };

    return new Food(color::Color(background_color), color::Color(food_color), std::move(food_frame));
  }
}
