#include "XProxy.hpp"
#include <cstring>


namespace xlib {

	XProxy::XProxy() = default;
	XProxy::~XProxy() = default;

	void XProxy::draw_rectangle(const geometry::Rectangle& r, const color::Color& color) {}
	void XProxy::fill_rectangle(const geometry::Rectangle& r, const color::Color& color) {}

	void XProxy::draw_circle(const geometry::Rectangle& r, const color::Color& color) {}
	void XProxy::fill_circle(const geometry::Rectangle& r, const color::Color& color) {}

	void XProxy::draw_text(const geometry::Point& p, const color::Color& color, const std::string& text) {}

  XWindowAttributes XProxy::get_window_attributes() { 
		XWindowAttributes wa;
		std::memset(&wa, 0, sizeof(wa));
		return wa;
	}

  const unsigned int XProxy::get_text_width(const std::string& text) {
		return 0u;
	}

  const unsigned int XProxy::get_text_height() {
		return 0u;
	}
}
