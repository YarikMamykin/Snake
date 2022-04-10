#include "gmock/gmock.h"
#include "views/GameOver/GameOver.hpp"

namespace color {
	ColorPallete::ColorPallete() = default;
}

namespace xlib {
	X11_ColorizedTextLabel::X11_ColorizedTextLabel() = default;
	X11_ColorizedTextLabel::X11_ColorizedTextLabel(const std::string& text, 
                            const geometry::Rectangle& frame, 
                            const color::COLOR_SCHEME_TYPE& color_scheme, 
														color::ColorPallete&& char_color_sequence){}
	X11_ColorizedTextLabel::~X11_ColorizedTextLabel() = default;
    
	void X11_ColorizedTextLabel::show(bool) {}
	void X11_ColorizedTextLabel::show_frame(bool) {}
	void X11_ColorizedTextLabel::set_center(const int& x, const int& y) {}

	void X11_ColorizedTextLabel::shift_colors(){}
	void X11_ColorizedTextLabel::update_char_colors(){}
}

namespace timing {
	Timer::Timer(const std::chrono::milliseconds timeout, 
                   std::function<void()> callback) {}
	Timer::~Timer() = default;
	void Timer::launch() noexcept {}
	void Timer::stop() noexcept {}
	bool Timer::running() const noexcept { return true; }
}

namespace views {
	GameOver::GameOver() : timer(std::chrono::milliseconds(0u), []{}) {}
	GameOver::~GameOver() = default;

	void GameOver::activate() {}
	void GameOver::handle_key_press(const KeySym& key_sym, const unsigned int& mask) {}
}
