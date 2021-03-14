#include "XlibWrapper.hpp"

namespace xlib {

	bool XlibWrapper::open_display() {
		display = XOpenDisplay(nullptr);
		if (display == nullptr) {
			std::cerr << "Cannot open display" << std::endl;
			return false;
		}
		return true;
	}

	void XlibWrapper::close_display() {
		XCloseDisplay(display);
	}

	bool XlibWrapper::create_graphical_context() {
		graphical_context = DefaultGC(display, XDefaultScreen(display));
		return true;
	}

	bool XlibWrapper::load_font(const char* font_name) {
		create_graphical_context();

		font_info = XLoadQueryFont(display, font_name);
		if(!font_info) {
			std::cerr << "FONT NOT LOADED!!!!" << std::endl;
			return false;
		}

		XSetFont(display, graphical_context, font_info->fid);
		return true;
	}

	void XlibWrapper::free_font() {
    XFreeFont(display, font_info);
	}

	bool XlibWrapper::create_window(geometry::Rectangle&& window_frame, 
																	color::COLOR_SCHEME_TYPE&& color_scheme, 
																	const unsigned int& border_width,
																	const char* name,
																	const char* font_name) {

		if(!open_display() || !load_font(font_name)) {
			return false;
		}

		window = XCreateSimpleWindow(display,
				RootWindow(display, XDefaultScreen(display)),
				window_frame.x, 
				window_frame.y, 
				window_frame.width, 
				window_frame.height,
				border_width,
				color_scheme.at(color::ColorSchemeID::FrameColor).to_long(), 
				color_scheme.at(color::ColorSchemeID::BackgroundColor).to_long());

		XStoreName(display, window, name);
		XMapWindow(display, window);

		window_color_scheme = color_scheme;
		return true;
	}

	XWindowAttributes XlibWrapper::get_window_attributes() {
    XWindowAttributes win_attr;
    XGetWindowAttributes(display, window, &win_attr);
		return win_attr;
	}

	void XlibWrapper::flush_buffer() {
		XFlush(display);
	}

	void XlibWrapper::redraw_window_background() {
		XFlushGC(display, graphical_context);
		XFlush(display);
		auto&& win_attr = get_window_attributes();
		fill_rectangle({0,0,win_attr.width, win_attr.height}, 
									 std::forward<color::Color>(window_color_scheme.at(color::ColorSchemeID::BackgroundColor)));
	}

	void XlibWrapper::destroy_window() {
		free_font();
		XDestroyWindow(display, window);
		close_display();
	}

	void XlibWrapper::draw_rectangle(geometry::Rectangle&& r, color::Color&& color) { 
		XSetLineAttributes(display, graphical_context, 3u,0,0,0);
		XSetForeground(display, graphical_context, color.to_long());
		XDrawRectangle(display, window, graphical_context, r.x, r.y, r.width, r.height);
	}

	void XlibWrapper::fill_rectangle(geometry::Rectangle&& r, color::Color&& color) {
		XSetForeground(display, graphical_context, color.to_long());
		XFillRectangle(display, window, graphical_context, r.x, r.y, r.width, r.height);
	}

	void XlibWrapper::draw_circle(geometry::Rectangle&& r, color::Color&& color) {
		XSetForeground(display, graphical_context, color.to_long());
		XDrawArc(display, window, graphical_context, r.x, r.y, r.width, r.height, 0, 360*64); // angle is specified as <degrees> * 64
	}

	void XlibWrapper::fill_circle(geometry::Rectangle&& r, color::Color&& color) {
		XSetForeground(display, graphical_context, color.to_long());
		XFillArc(display, window, graphical_context, r.x, r.y, r.width, r.height, 0, 360*64); // angle is specified as <degrees> * 64
	}

	void XlibWrapper::draw_text(geometry::Point&& p, color::Color&& color, const std::string& text) {
    XSetForeground(display, graphical_context, color.to_long());
    XDrawString(display, window, graphical_context, p.x, p.y, text.c_str(), text.length());
	}

	const unsigned int XlibWrapper::get_text_width(const std::string& text) {
    return XTextWidth(font_info, text.c_str(), text.size());
	}

	const unsigned int XlibWrapper::get_text_height() {
    return font_info->ascent + font_info->descent;
	}

	void XlibWrapper::select_events_to_process() {
		XSelectInput(display, window, ExposureMask | KeyPressMask | ButtonPressMask | PointerMotionMask );
	}

	void XlibWrapper::next_event(XEvent* event) {
		XNextEvent(display, event);
	}

	bool XlibWrapper::event_in_queue(int event_type, XEvent* event) {
		return XCheckTypedEvent(display, event_type, event);
	}

	const color::COLOR_SCHEME_TYPE& XlibWrapper::get_window_colorscheme() const {
		return window_color_scheme;
	}

	std::shared_ptr<XlibWrapper> XlibWrapper::self() {
		static auto _self = std::make_shared<XlibWrapper>();
		return _self;
	}

}
