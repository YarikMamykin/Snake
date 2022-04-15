#include "commands/graphics_commands/FillCircle/FillCircle.hpp"
#include "MockFillCircle.hpp"
#include "MockXProxy.hpp"

std::list<std::unique_ptr<commands::Command>> MockFillCircle::commands_collector;

namespace commands {
	void Command::push_xlib_command(std::unique_ptr<Command> command) {
		MockFillCircle::commands_collector.push_back(std::move(command));
	}
}

namespace commands {
	FillCircle::FillCircle(
			const geometry::Rectangle& circle_frame,
			const color::Color& color) : GraphicsCommand(circle_frame, color) { }

	void FillCircle::execute(xlib::XProxy& proxy) { 
		proxy.fill_circle(rectangle, color);
	}
}

