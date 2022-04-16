#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "helpers/Helper.hpp"
#include "commands/ChangeView/ChangeView.hpp"

views::ViewID view_id_passed;

namespace helpers {
	void Helper::SendChangeViewEvent(xlib::XProxy&, const views::ViewID& viewID) {
		view_id_passed = viewID;
	}
}

namespace xlib {
	struct XProxy {};
}

namespace commands_test {

	TEST(ChangeViewTest, Execute)
	{
		constexpr auto expected_view_id = views::ViewID::ABOUT;
		commands::ChangeView cv { views::ViewID(expected_view_id) };

		xlib::XProxy xp;
		cv.execute(xp);

		EXPECT_EQ(view_id_passed, expected_view_id);
	}
}
