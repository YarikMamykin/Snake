#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "MockMenu.hpp"
#define private public
#include <views/GameMenu/GameMenu.hpp>
#include <commands/Command/Command.hpp>
#include <helpers/Helper.hpp>

std::list<std::unique_ptr<commands::Command>> mock_command_queue;

namespace commands {
	void Command::push_xlib_command(std::unique_ptr<Command> command) {
		mock_command_queue.push_back(std::move(command));
	}
}

views::ViewID actual_view_id { views::ViewID::NONE };
bool exit_app_sent { false };

namespace helpers {
	void Helper::SendChangeViewEvent(xlib::XProxy&, const views::ViewID &view_id) {
		actual_view_id = view_id;
	}
	void Helper::SendExitApplicationEvent(xlib::XProxy&) {
		exit_app_sent = true;
	}
}

namespace xlib {
	struct XProxy {};
}

struct GameMenuTests : public testing::Test {
	void TearDown() override {
		mock_command_queue.clear();
		actual_view_id = views::ViewID::NONE;
	}
};


TEST_F(GameMenuTests, Activate) 
{
	views::GameMenu ga;
	auto menu_mock = new MockMenu();
	ga.menu.reset(menu_mock);

	auto* current_item_mock = new MockCurrentItem();
	std::list<std::unique_ptr<abstractions::ui::Object>> items_list;
	items_list.emplace_back(current_item_mock);

	EXPECT_CALL(*menu_mock, set_center);
	EXPECT_CALL(*menu_mock, get_current_item).WillOnce(testing::Return(items_list.begin()));
	EXPECT_CALL(*current_item_mock, set_focused(true));
	EXPECT_CALL(*menu_mock, show(true));
	
	ga.activate();
}

TEST_F(GameMenuTests, HandleKeyPress_KeyDown)
{
	views::GameMenu ga;
	auto menu_mock = new MockMenu();
	ga.menu.reset(menu_mock);

	auto* current_item_mock = new MockCurrentItem();
	std::list<std::unique_ptr<abstractions::ui::Object>> items_list;
	items_list.emplace_back(current_item_mock);

	EXPECT_CALL(*menu_mock, move_to_next_item);
	EXPECT_CALL(*menu_mock, set_center);
	EXPECT_CALL(*menu_mock, get_current_item).WillOnce(testing::Return(items_list.begin()));
	EXPECT_CALL(*current_item_mock, set_focused(true));
	EXPECT_CALL(*menu_mock, show(true));

	ga.handle_key_press(XK_Down, 0);
}

TEST_F(GameMenuTests, HandleKeyPress_KeyUp)
{
	views::GameMenu ga;
	auto menu_mock = new MockMenu();
	ga.menu.reset(menu_mock);

	auto* current_item_mock = new MockCurrentItem();
	std::list<std::unique_ptr<abstractions::ui::Object>> items_list;
	items_list.emplace_back(current_item_mock);

	EXPECT_CALL(*menu_mock, move_to_prev_item);
	EXPECT_CALL(*menu_mock, set_center);
	EXPECT_CALL(*menu_mock, get_current_item).WillOnce(testing::Return(items_list.begin()));
	EXPECT_CALL(*current_item_mock, set_focused(true));
	EXPECT_CALL(*menu_mock, show(true));
	
	ga.handle_key_press(XK_Up, 0);
}
