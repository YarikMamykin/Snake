#pragma once
#include <color/Color/Color.hpp>
#include <geometry/Rectangle.hpp>

namespace xlib {
	struct XProxy {
		virtual void fill_circle(const geometry::Rectangle& r, const color::Color& c) = 0;
		virtual ~XProxy() = default;
	};
}
