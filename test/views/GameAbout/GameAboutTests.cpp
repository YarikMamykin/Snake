#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <views/GameAbout/GameAbout.hpp>
#include <commands/Command/Command.hpp>
#include <commands/ChangeView/ChangeView.hpp>
#include <helpers/Helper.hpp>
#include "MockTextLabel.hpp"

std::list<std::unique_ptr<commands::Command>> mock_command_queue;

namespace commands {
	void Command::push_xlib_command(std::unique_ptr<Command> command) {
		mock_command_queue.push_back(std::move(command));
	}
}

struct GameAboutTests : public testing::Test {
	void TearDown() override {
		mock_command_queue.clear();
	}
};

TEST_F(GameAboutTests, Activate) 
{
	auto* mock_tl = new MockTextLabel();
	views::GameAbout ga(mock_tl);
	EXPECT_CALL(*mock_tl, set_center);
	EXPECT_CALL(*mock_tl, show(true));
	ga.activate();
}

TEST_F(GameAboutTests, HandleKeyPress) 
{
	auto* mock_tl = new MockTextLabel();
	views::GameAbout ga(mock_tl);

	KeySym escape_key_sym { XK_Escape };
	ga.handle_key_press(escape_key_sym, 0);

	ASSERT_EQ(mock_command_queue.size(), 1ul);
	ASSERT_TRUE(dynamic_cast<commands::ChangeView*>(mock_command_queue.front().get()));
}
