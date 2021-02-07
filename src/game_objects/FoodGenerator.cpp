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
    return {x > region.x ? x : region.x + x , y > region.y ? y : region.y + y};
  }
}

namespace game_objects {
  FoodGenerator::FoodGenerator() 
  : points_generator(configuration::Settings::get_concrete<configuration::RANDOM_ENGINE_SEED_SEQUENCE_TYPE>(configuration::ConfigID::RANDOM_ENGINE_SEED_SEQUENCE)) {
  }

  Food* FoodGenerator::generate(xlib::X11_Window* x_window, geometry::Rectangle&& region) {
    auto&& window_width = x_window->get_width();
    auto&& window_height = x_window->get_height();
    auto background_color = x_window->get_color_scheme().at(color::ColorSchemeID::BackgroundColor);
    auto&& food_color = configuration::Settings::get_concrete<color::ColorPallete>(configuration::ConfigID::FOOD_COLOR).get_current_color();
    auto&& food_size = configuration::Settings::get_concrete<configuration::RESTRICTED_UINT>(configuration::ConfigID::FOOD_SIZE).get_restricted_value();
    auto&& generated_point = points_generator.generate_point(std::move(region));
    return new Food(std::forward<decltype(background_color)>(background_color), 
                    std::forward<decltype(food_color)>(food_color), 
                    { generated_point.x, 
                    generated_point.y, 
                    food_size, 
                    food_size });
  }
}
