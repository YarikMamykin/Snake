#include "FoodGenerator.hpp"
#include "Point.hpp"

namespace game_objects {
  RandomEngine::RandomEngine(const unsigned int& min, const unsigned int& max, std::list<unsigned int>&& seed_sequence) {
    std::seed_seq sequence(seed_sequence.begin(), seed_sequence.end());
    algorithm.seed(sequence);
  }

  geometry::Point RandomEngine::generate_point() {
    int&& x = algorithm();
    int&& y = algorithm();
    return {x,y};
  }
}

namespace game_objects {
  FoodGenerator::FoodGenerator() 
  : points_generator(configuration::Settings::get_concrete<configuration::RANDOM_ENGINE_ALGORITHM_TYPE>(configuration::ConfigID::RANDOM_ENGINE_ALGORITHM).min(),
                     configuration::Settings::get_concrete<configuration::RANDOM_ENGINE_ALGORITHM_TYPE>(configuration::ConfigID::RANDOM_ENGINE_ALGORITHM).max(),
                     configuration::Settings::get_concrete<configuration::RANDOM_ENGINE_SEED_SEQUENCE_TYPE>(configuration::ConfigID::RANDOM_ENGINE_SEED_SEQUENCE)) {
  }

  Food FoodGenerator::generate(xlib::X11_Window* x_window) {
    auto&& window_width = x_window->get_width();
    auto&& window_height = x_window->get_height();
    auto&& background_color = x_window->get_color_scheme().at(color::ColorSchemeID::BackgroundColor);
    auto&& food_color = configuration::Settings::get_concrete<color::Color>(configuration::ConfigID::FOOD_COLOR);
    auto&& food_size = configuration::Settings::get_concrete<configuration::RESTRICTED_UINT>(configuration::ConfigID::FOOD_SIZE);
    auto&& generated_point = points_generator.generate_point();
    return Food(std::move(background_color), std::move(food_color), { generated_point.x, generated_point.y, food_size.get_restricted_value(), food_size.get_restricted_value() });
  }
}
