#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <commands/graphics_commands/DrawRectangle/DrawRectangle.hpp>
#include <commands/graphics_commands/DrawCircle/DrawCircle.hpp>
#include <commands/graphics_commands/DrawText/DrawText.hpp>
#include <commands/graphics_commands/FillRectangle/FillRectangle.hpp>
#include <commands/graphics_commands/FillCircle/FillCircle.hpp>
#include <xlib/XProxy/MockXProxy.hpp>
#include <color/Color/Color.hpp>
#include <geometry/Rectangle.hpp>


TEST(DrawRectangleTest, Execute) 
{
	const geometry::Rectangle r {0,0, 100, 100};
	const color::Color c { 10ul };
	commands::DrawRectangle dr { r, c };
	
	xlib::MockXProxy xp;
	geometry::Rectangle actual_r;
	color::Color actual_c { 0ul };

	EXPECT_CALL(xp, draw_rectangle).WillOnce(
			testing::DoAll(
				testing::SaveArg<0>(&actual_r), 
				testing::SaveArg<1>(&actual_c)));
	
	dr.execute(xp);

	EXPECT_EQ(r, actual_r);
	EXPECT_EQ(c, actual_c);
}

TEST(DrawCircleTest, Execute) 
{
	const geometry::Rectangle r {0,0, 100, 100};
	const color::Color c { 10ul };
	commands::DrawCircle dc { r, c };
	
	xlib::MockXProxy xp;
	geometry::Rectangle actual_r;
	color::Color actual_c { 0ul };

	EXPECT_CALL(xp, draw_circle).WillOnce(
			testing::DoAll(
				testing::SaveArg<0>(&actual_r), 
				testing::SaveArg<1>(&actual_c)));
	
	dc.execute(xp);

	EXPECT_EQ(r, actual_r);
	EXPECT_EQ(c, actual_c);
}

TEST(FillRectangleTest, Execute) 
{
	const geometry::Rectangle r {0,0, 100, 100};
	const color::Color c { 10ul };
	commands::FillRectangle fr { r, c };
	
	xlib::MockXProxy xp;
	geometry::Rectangle actual_r;
	color::Color actual_c { 0ul };

	EXPECT_CALL(xp, fill_rectangle).WillOnce(
			testing::DoAll(
				testing::SaveArg<0>(&actual_r), 
				testing::SaveArg<1>(&actual_c)));
	
	fr.execute(xp);

	EXPECT_EQ(r, actual_r);
	EXPECT_EQ(c, actual_c);
}

TEST(FillCircleTest, Execute) 
{
	const geometry::Rectangle r {0,0, 100, 100};
	const color::Color c { 10ul };
	commands::FillCircle fc { r, c };
	
	xlib::MockXProxy xp;
	geometry::Rectangle actual_r;
	color::Color actual_c { 0ul };

	EXPECT_CALL(xp, fill_circle).WillOnce(
			testing::DoAll(
				testing::SaveArg<0>(&actual_r), 
				testing::SaveArg<1>(&actual_c)));
	
	fc.execute(xp);

	EXPECT_EQ(r, actual_r);
	EXPECT_EQ(c, actual_c);
}

TEST(DrawText, Execute) 
{
	const geometry::Point p {100, 100};
	const color::Color c { 10ul };
	const std::string t { "test text" };

	commands::DrawText dt { t,p,c };
	
	xlib::MockXProxy xp;
	geometry::Point actual_p;
	color::Color actual_c { 0ul };
	std::string actual_t;

	EXPECT_CALL(xp, draw_text).WillOnce(
			testing::DoAll(
				testing::SaveArg<0>(&actual_p), 
				testing::SaveArg<1>(&actual_c),
				testing::SaveArg<2>(&actual_t)));
	
	dt.execute(xp);

	EXPECT_EQ(p, actual_p);
	EXPECT_EQ(c, actual_c);
	EXPECT_EQ(t, actual_t);
}
