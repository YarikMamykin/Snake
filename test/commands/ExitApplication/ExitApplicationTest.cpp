#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <helpers/Helper.hpp>
#include <commands/ExitApplication/ExitApplication.hpp>

bool exit_application_command_sent { false };

namespace helpers {
	void Helper::SendExitApplicationEvent(xlib::XProxy&) {
		exit_application_command_sent = true;
	}
}

namespace xlib {
	struct XProxy {};
}

namespace commands_test {

	TEST(ExitApplicationTest, Execute)
	{
		commands::ExitApplication ea;

		xlib::XProxy xp;
		ea.execute(xp);

		EXPECT_TRUE(exit_application_command_sent);
	}
}
