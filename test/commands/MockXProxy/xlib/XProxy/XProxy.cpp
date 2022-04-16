#include "XProxy.hpp"


namespace xlib {

	XProxy::XProxy() = default;
	XProxy::~XProxy() = default;

	void XProxy::draw_rectangle(const geometry::Rectangle& r, const color::Color& color) {}
	void XProxy::fill_rectangle(const geometry::Rectangle& r, const color::Color& color) {}

	void XProxy::draw_circle(const geometry::Rectangle& r, const color::Color& color) {}
	void XProxy::fill_circle(const geometry::Rectangle& r, const color::Color& color) {}

	void XProxy::draw_text(const geometry::Point& p, const color::Color& color, const std::string& text) {}
}
