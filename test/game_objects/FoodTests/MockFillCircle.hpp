#pragma once
#include <list>
#include <memory>
#include <commands/Command/Command.hpp>

struct MockFillCircle {
	static std::list<std::unique_ptr<commands::Command>> commands_collector;
};
