#include "game_objects/Info.hpp"

#include "color/Color.hpp"
#include "geometry/Rectangle.hpp"
#include "configuration/Settings.hpp"

namespace {
  color::COLOR_SCHEME_TYPE color_scheme = {
    { color::ColorSchemeID::BackgroundColor, 0UL },
    { color::ColorSchemeID::FrameColor, ~0UL },
    { color::ColorSchemeID::TextColor, ~0UL }
  };

  constexpr unsigned int vertical_offset = 5u;
  constexpr unsigned int horizontal_offset = 5u;
}

namespace game_objects {
  Info::Info()
    : score(std::make_unique<xlib::X11_TextLabel>("Score: 00000", geometry::Rectangle{}, color_scheme))
    , time(std::make_unique<xlib::X11_TextLabel>("00:00:000", geometry::Rectangle{}, color_scheme)) { 
      const auto& win_frame = config::get_concrete_ref<geometry::Rectangle>(config_id::WINDOW_FRAME);
      auto&& score_width = score->get_width();
      auto&& score_height = score->get_height();
      auto&& time_width = time->get_width();
      auto&& time_height = time->get_height();
      score->set_center(horizontal_offset + score_width/2u, vertical_offset + score_height/2u);
      time->set_center(win_frame.width - horizontal_offset - time_width/2u, vertical_offset + time_height/2u);
    }

    void Info::update_score(unsigned int new_score) {
      score->set_text(std::string("Score: ") + std::to_string(new_score));
      score->show(true);
    }

    void Info::update_time(std::chrono::milliseconds new_time) {
      std::string result;
      auto&& minutes = std::chrono::duration_cast<std::chrono::minutes>(new_time).count();
      auto&& seconds = std::chrono::duration_cast<std::chrono::seconds>(new_time).count();
      auto&& mills = std::chrono::duration_cast<std::chrono::milliseconds>(new_time).count() % 1000;
      if(minutes < 10u) {
        result = "0";
      }
      result += std::to_string(minutes);
      result += ":";
      if(seconds < 10u) {
        result += "0";
      }
      result += std::to_string(seconds);
      result += ":";
      if(mills < 10u) {
        result += "00";
      }
      if(mills < 100u) {
        result += "0";
      }
      result += std::to_string(mills);

      time->set_text(result);
      time->show(true);
    }

    void Info::update(unsigned int new_score, std::chrono::milliseconds new_time) {
      update_score(new_score);
      update_time(new_time);
    }
}
