#include "X11_ColorizedTextLabel.hpp"
#include <algorithm>
#include <numeric>

namespace xlib {
  X11_ColorizedTextLabel::X11_ColorizedTextLabel() : abstractions::ui::TextLabel() {}

  X11_ColorizedTextLabel::X11_ColorizedTextLabel(const std::string& text, 
                               const geometry::Rectangle& frame, 
                               const color::COLOR_SCHEME_TYPE& color_scheme, 
															 color::ColorPallete&& char_color_sequence) 
  : abstractions::ui::TextLabel(text, frame, color_scheme) 
	, char_color_sequence(char_color_sequence) {
    std::transform(text.begin(), text.end(), std::back_inserter(char_labels), 
				[&color_scheme](const char& c) -> xlib::X11_TextLabel {
        return xlib::X11_TextLabel(std::string(1,c), {}, color_scheme);
		});

		this->frame.height = char_labels.empty() ? 0u : char_labels.front().get_width();
		this->frame.width = std::accumulate(char_labels.begin(), char_labels.end(), 0u, 
				[](unsigned int w, const xlib::X11_TextLabel& char_label) -> unsigned int {
				return w + char_label.get_width();
		});
  }

  X11_ColorizedTextLabel::~X11_ColorizedTextLabel() { }

  void X11_ColorizedTextLabel::show(bool show_flag) {
    if(show_flag) {
			update_char_colors();
    }

    if(!show_flag) {
    }
  }

  void X11_ColorizedTextLabel::show_frame(bool) { }

	void X11_ColorizedTextLabel::set_center(const int& x, const int& y) {
		abstractions::ui::TextLabel::set_center(x,y);

		if(!char_labels.empty()) {
			auto char_labels_it = char_labels.begin();
			char_labels_it->set_position(this->frame.x,this->frame.y);
			while((char_labels_it = std::next(char_labels_it)) != char_labels.end()) {
				const auto&& prev_top_right = std::prev(char_labels_it)->get_frame().top_right();
				char_labels_it->set_position(prev_top_right.x, prev_top_right.y);
			}
		}
	}

	void X11_ColorizedTextLabel::shift_colors() {
		++char_color_sequence;
		update_char_colors();
	}

	void X11_ColorizedTextLabel::update_char_colors() {
		for(auto& char_label : char_labels) {
			char_label.update_color_scheme(color::ColorSchemeID::TextColor, char_color_sequence.get_current_color());
			char_label.show(true);
			++char_color_sequence;
		}
	}
}

