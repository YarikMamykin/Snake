#include "FoodGenerator.hpp"
#include "Point.hpp"
#include "ColorPallete.hpp"

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
    int&& x = algorithm();
    int&& y = x ^ (algorithm()/(algorithm()+7));
    y = x ^ algorithm();
    x = y ^ algorithm();
    const bool x_in_range = x >= region.x && x <= (region.x + region.width);
    const bool y_in_range = y >= region.y && y <= (region.y + region.height);
    return {x_in_range ? x : region.x, y_in_range ? y : region.y};
  }
}

namespace game_objects {
  FoodGenerator::FoodGenerator() 
  : points_generator(configuration::Settings::get_concrete<configuration::RANDOM_ENGINE_SEED_SEQUENCE_TYPE>(configuration::ConfigID::RANDOM_ENGINE_SEED_SEQUENCE)) {
  }

  Food* FoodGenerator::generate(xlib::X11_Window* x_window) {
    auto&& window_width = x_window->get_width();
    auto&& window_height = x_window->get_height();
    auto background_color = x_window->get_color_scheme().at(color::ColorSchemeID::BackgroundColor);
    auto&& food_color = configuration::Settings::get_concrete<color::ColorPallete>(configuration::ConfigID::FOOD_COLOR).get_current_color();
    auto&& food_size = configuration::Settings::get_concrete<configuration::RESTRICTED_UINT>(configuration::ConfigID::FOOD_SIZE).get_restricted_value();
    auto&& region = geometry::Rectangle{50,50,x_window->get_width() - 50u,x_window->get_height() - 50u};
    auto&& generated_point = points_generator.generate_point(std::move(region));
    return new Food(std::forward<decltype(background_color)>(background_color), 
                    std::forward<decltype(food_color)>(food_color), 
                    { generated_point.x, 
                    generated_point.y, 
                    food_size, 
                    food_size });
  }
}
