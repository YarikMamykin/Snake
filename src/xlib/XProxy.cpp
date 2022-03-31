#include "XProxy.hpp"

namespace {
	color::Color background { 0ul };
}

namespace xlib {

	XProxy::XProxy(std::unique_ptr<XSettings> settings, XError& err) {
		err = init_X_system(std::move(settings));
	}

	std::variant<std::reference_wrapper<XProxy>, XError> 
		XProxy::create(std::unique_ptr<XSettings> settings) noexcept {

			XError error { XError::NONE };
			static XProxy self(std::move(settings), error);

			if(XError::NONE == error)
				return self;

			return error;
	}

	XProxy::~XProxy() = default;

	XError XProxy::init_X_system(std::unique_ptr<XSettings> settings) {

		const auto& [ 
			font_name, 
			window_name,
			window_geometry,
			border_width,
			window_color_scheme
		] = *settings;

		auto& [ 
			display, 
			screen, 
			graphical_context, 
			window, 
			font_info 
		] = m_handlers;

		display = XOpenDisplay(nullptr);
		if(display == nullptr)
			return XError::OPEN_DISPLAY_ERROR;

		screen = XDefaultScreen(display);
		graphical_context = DefaultGC(display, screen);

		font_info = XLoadQueryFont(display, font_name.c_str());
		if(!font_info)
			return XError::FONT_LOAD_ERROR;

		XSetFont(display, graphical_context, font_info->fid);

		window = XCreateSimpleWindow(display,
				RootWindow(display, screen),
				window_geometry.x,
				window_geometry.y,
				window_geometry.w,
				window_geometry.h,
				border_width,
				window_color_scheme.at(color::ColorSchemeID::FrameColor),
				window_color_scheme.at(color::ColorSchemeID::BackgroundColor));

		if(!window)
			return XError::CREATE_WINDOW_ERROR;

		background = window_color_scheme.at(color::ColorSchemeID::BackgroundColor);

		XStoreName(display, window, window_name.c_str());
		XMapWindow(display, window);

		XSelectInput(m_handlers.display, m_handlers.window, ExposureMask | KeyPressMask | ButtonPressMask | PointerMotionMask );

		return XError::NONE;
	}

	XError XProxy::deinit_X_system() {
		XFreeFont(m_handlers.display, m_handlers.font_info);
		XDestroyWindow(m_handlers.display, m_handlers.window);
		XCloseDisplay(m_handlers.display);
		return XError::NONE;
	}

	XWindowAttributes XProxy::get_window_attributes() {
		XWindowAttributes win_attr;
		XGetWindowAttributes(m_handlers.display, m_handlers.window, &win_attr);
		return win_attr;
	}

	void XProxy::flush_buffer() {
		XFlush(m_handlers.display);
	}

	void XProxy::redraw_window_background() {
		XFlushGC(m_handlers.display, m_handlers.graphical_context);
		flush_buffer();
		auto win_attr = get_window_attributes();
		fill_rectangle({0,0,win_attr.width, win_attr.height}, background);
	}

	void XProxy::draw_rectangle(const geometry::Rectangle& r, const color::Color& color) {
		XSetLineAttributes(m_handlers.display, m_handlers.graphical_context, 3u,0,0,0);
		XSetForeground(m_handlers.display, m_handlers.graphical_context, color);
		XDrawRectangle(m_handlers.display, 
				m_handlers.window, 
				m_handlers.graphical_context, 
				r.x, r.y, r.width, r.height);
	}

	void XProxy::fill_rectangle(const geometry::Rectangle& r, const color::Color& color) {
		XSetForeground(m_handlers.display, m_handlers.graphical_context, color);
		XFillRectangle(m_handlers.display, m_handlers.window, 
				m_handlers.graphical_context, 
				r.x, r.y, r.width, r.height);
	}

	void XProxy::draw_circle(const geometry::Rectangle& r, const color::Color& color) {
		XSetForeground(m_handlers.display, m_handlers.graphical_context, color);
		XDrawArc(m_handlers.display, m_handlers.window, m_handlers.graphical_context, r.x, r.y, r.width, r.height, 0, 360*64); // angle is specified as <degrees> * 64
	}

	void XProxy::fill_circle(const geometry::Rectangle& r, const color::Color& color) {
		XSetForeground(m_handlers.display, m_handlers.graphical_context, color);
		XFillArc(m_handlers.display, m_handlers.window, m_handlers.graphical_context, r.x, r.y, r.width, r.height, 0, 360*64); // angle is specified as <degrees> * 64
	}

	void XProxy::draw_text(const geometry::Point& p, const color::Color& color, const std::string& text) {
		XSetForeground(m_handlers.display, m_handlers.graphical_context, color);
		XDrawString(m_handlers.display, m_handlers.window, m_handlers.graphical_context, p.x, p.y, text.c_str(), text.length());
	}

	const unsigned int XProxy::get_text_width(const std::string& text) {
		return XTextWidth(m_handlers.font_info, text.c_str(), text.size());
	}

	const unsigned int XProxy::get_text_height() {
		return m_handlers.font_info->ascent + m_handlers.font_info->descent;
	}

	void XProxy::next_event(XEvent* event) {
		XNextEvent(m_handlers.display, event);
	}

	void XProxy::send_event(long event_mask, XEvent* event) {
		XSendEvent(m_handlers.display, m_handlers.window, true, event_mask, event);
	}

	bool XProxy::event_in_queue(int event_type, XEvent* event) {
		return XCheckTypedEvent(m_handlers.display, event_type, event);
	}

}
