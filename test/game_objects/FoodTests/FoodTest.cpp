#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <game_objects/Food/Food.hpp>
#include "MockFillCircle.hpp"
#include "MockXProxy.hpp"
#include <configuration/Settings.hpp>


namespace game_objects_test {

struct FoodTest : public ::testing::Test { 
	void create_and_delete_food(
			const color::Color& expected_background_color,
			const color::Color& expected_color,
			const geometry::Rectangle& expected_frame) {

		auto f = game_objects::Food ( 
				color::Color(expected_background_color), 
				color::Color(expected_color), 
				geometry::Rectangle(expected_frame) );

		// small wait so timer inside food could start properly
		std::mutex m;
		std::unique_lock<std::mutex> lk(m);
		std::condition_variable cv;
		cv.wait_for(lk, configuration::Settings::get_concrete<std::chrono::milliseconds>(configuration::ConfigID::SNAKE_TIMEOUT) + std::chrono::milliseconds(1u));
	}
};

TEST_F(FoodTest, CreateFood)
{
	color::Color expected_background_color { 0ul };
	color::Color expected_color { 255ul };
	geometry::Rectangle expected_frame { 0,0, 250, 250 };

	create_and_delete_food(expected_background_color, expected_color, expected_frame);
	ASSERT_EQ(MockFillCircle::commands_collector.size(), 2ul);

	xlib::MockXProxy xmock;
	EXPECT_CALL(xmock, fill_circle(testing::_, testing::_)).Times(2);
	for(auto& command: MockFillCircle::commands_collector) {
		command->execute(xmock);
	}
}
}
