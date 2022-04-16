#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstring>
#include <commands/synchronous_commands/QueryTextHeight/QueryTextHeight.hpp>
#include <commands/synchronous_commands/QueryTextWidth/QueryTextWidth.hpp>
#include <commands/synchronous_commands/QueryWindowFrame/QueryWindowFrame.hpp>
#include <xlib/XProxy/MockXProxy.hpp>
#include <color/Color/Color.hpp>
#include <geometry/Rectangle.hpp>
#include <commands/synchronous_commands/QueryLock/QueryLock.hpp>
#include "AWindowMock.hpp"


TEST(QueryTextHeight, Execute) 
{
	constexpr unsigned int expected_result { 10u };

	unsigned int actual_result { 0u };
	commands::QueryLock ql;
	commands::QueryTextHeight query_th { actual_result, ql };
	
	xlib::MockXProxy xp;

	ON_CALL(xp, get_text_height).WillByDefault(testing::Return(expected_result));
	EXPECT_CALL(xp, get_text_height).WillOnce(testing::Return(expected_result));
	
	query_th.execute(xp);

	EXPECT_EQ(actual_result, expected_result);
}

TEST(QueryTextWidth, Execute) 
{
	unsigned int actual_result { 0u };
	const std::string test_text {"test text"};
	const auto expected_result { test_text.size() };

	commands::QueryLock ql;
	commands::QueryTextWidth query_tw { test_text, actual_result, ql };
	
	xlib::MockXProxy xp;

	ON_CALL(xp, get_text_width).WillByDefault(testing::Return(0u));
	EXPECT_CALL(xp, get_text_width(test_text)).
		WillOnce(testing::Return(expected_result));
	
	query_tw.execute(xp);

	EXPECT_EQ(actual_result, expected_result);
}

TEST(QueryWindowFrame, Execute) 
{
	constexpr unsigned int expected_width { 10u };
	constexpr unsigned int expected_height { 20u };

	AWindowMock wmock;
	commands::QueryLock ql;
	commands::QueryWindowFrame query_wf { &wmock, ql };
	
	xlib::MockXProxy xp;

	XWindowAttributes default_attrs { 
		.width = expected_width,
		.height = expected_height
	};

	ON_CALL(xp, get_window_attributes)
		.WillByDefault(testing::Return(default_attrs));

	EXPECT_CALL(xp, get_window_attributes)
		.WillOnce(testing::Return(default_attrs)); 

	unsigned int actual_width {0u};
	EXPECT_CALL(wmock, set_width)
		.WillOnce(testing::SaveArg<0>(&actual_width));

	unsigned int actual_height {0u};
	EXPECT_CALL(wmock, set_height)
		.WillOnce(testing::SaveArg<0>(&actual_height));
	
	query_wf.execute(xp);

	EXPECT_EQ(actual_width, expected_width);
	EXPECT_EQ(actual_height, expected_height);
}
