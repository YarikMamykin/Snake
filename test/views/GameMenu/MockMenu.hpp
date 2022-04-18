#pragma once
#include <gmock/gmock.h>
#include <abstractions/ui/Object.hpp>
#include <abstractions/ui/Menu.hpp>
#include <geometry/Point.hpp>
#include <list>
#include <memory>

struct MockMenu : public abstractions::ui::Menu {
	MockMenu() 
		: abstractions::ui::Menu(ui::LayoutType::HORIZONTAL, {}, {}) {}
	MOCK_METHOD(void, show, (bool), (override));
	MOCK_METHOD(void, show_frame, (bool), (override));
	MOCK_METHOD(void, set_center, (const int& x, const int& y), (override));
	MOCK_METHOD(
			std::list<std::unique_ptr<abstractions::ui::Object>>::iterator, 
			get_current_item, (), (const override));
	MOCK_METHOD(void, move_to_next_item, (), (override));
	MOCK_METHOD(void, move_to_prev_item, (), (override));
};

struct MockCurrentItem : public abstractions::ui::Object {
	MockCurrentItem() = default;
	MOCK_METHOD(void, show, (bool), (override));
	MOCK_METHOD(void, show_frame, (bool), (override));
	MOCK_METHOD(void, set_focused, (bool), (override));
};
