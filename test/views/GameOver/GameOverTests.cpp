#include <gtest/gtest.h>
#include <gmock/gmock.h>
#define private public
#include <views/GameOver/GameOver.hpp>
#include <commands/Command/Command.hpp>
#include <helpers/Helper.hpp>

std::list<std::unique_ptr<commands::Command>> mock_command_queue;

namespace commands {
	void Command::push_xlib_command(std::unique_ptr<Command> command) {
		mock_command_queue.push_back(std::move(command));
	}
}

views::ViewID actual_view_id { views::ViewID::NONE };

namespace helpers {
	void Helper::SendChangeViewEvent(xlib::XProxy&, const views::ViewID &view_id) {
		actual_view_id = view_id;
	}
}

namespace xlib {
	struct XProxy {};
}

struct GameOverTests : public testing::Test {
	void TearDown() override {
		mock_command_queue.clear();
		actual_view_id = views::ViewID::NONE;
	}
};

TEST_F(GameOverTests, Activate) 
{
	views::GameOver ga;
	
	auto* colorized_text_label_mock = ga.colorized_text_label.get();
	auto& timer_mock = ga.timer;

	EXPECT_CALL(*colorized_text_label_mock, set_center);
	EXPECT_CALL(timer_mock, launch);

	ga.activate();
}

TEST_F(GameOverTests, HandleKeyPress) 
{
	views::GameOver ga;
	ga.handle_key_press(XK_Escape, 0);
	ASSERT_EQ(mock_command_queue.size(), 1ul);

	xlib::XProxy mock_xp;
	mock_command_queue.front()->execute(mock_xp);
	EXPECT_EQ(actual_view_id, views::ViewID::MENU);
}
