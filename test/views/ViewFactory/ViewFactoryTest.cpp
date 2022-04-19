#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "views/ViewFactory.hpp"
#include <limits>

namespace views_test {

struct ViewsTest : public ::testing::Test {
};

TEST_F(ViewsTest, MenuId)
{
    views::ViewFactory factory;
    auto result = factory.get_view(views::ViewID::MENU);

    constexpr bool result_is_view = std::is_same<decltype(result), std::unique_ptr<views::View>>::value;
    EXPECT_TRUE(result_is_view);

    const views::GameMenu* game_menu = dynamic_cast<views::GameMenu*>(result.get());
    EXPECT_TRUE(game_menu != nullptr);
}

TEST_F(ViewsTest, ActionId)
{
    views::ViewFactory factory;
    auto result = factory.get_view(views::ViewID::ACTION);

    constexpr bool result_is_view = std::is_same<decltype(result), std::unique_ptr<views::View>>::value;
    EXPECT_TRUE(result_is_view);

    const views::GameAction* game_action = dynamic_cast<views::GameAction*>(result.get());
    EXPECT_TRUE(game_action != nullptr);
}

TEST_F(ViewsTest, OverId)
{
    views::ViewFactory factory;
    auto result = factory.get_view(views::ViewID::OVER);

    constexpr bool result_is_view = std::is_same<decltype(result), std::unique_ptr<views::View>>::value;
    EXPECT_TRUE(result_is_view);

    const views::GameOver* game_over = dynamic_cast<views::GameOver*>(result.get());
    EXPECT_TRUE(game_over != nullptr);
}

TEST_F(ViewsTest, SettingId)
{
    views::ViewFactory factory;
    auto result = factory.get_view(views::ViewID::SETTINGS);

    constexpr bool result_is_view = std::is_same<decltype(result), std::unique_ptr<views::View>>::value;
    EXPECT_TRUE(result_is_view);

    const views::GameSettings* game_settings = dynamic_cast<views::GameSettings*>(result.get());
    EXPECT_TRUE(game_settings != nullptr);
}

TEST_F(ViewsTest, AboutId)
{
    views::ViewFactory factory;
    auto result = factory.get_view(views::ViewID::ABOUT);

    constexpr bool result_is_view = std::is_same<decltype(result), std::unique_ptr<views::View>>::value;
    EXPECT_TRUE(result_is_view);

    const views::GameAbout* game_about = dynamic_cast<views::GameAbout*>(result.get());
    EXPECT_TRUE(game_about != nullptr);
}

TEST_F(ViewsTest, InvalidId)
{
    views::ViewFactory factory;
    auto result = factory.get_view(static_cast<views::ViewID>(std::numeric_limits<int>::max()));

    constexpr bool result_is_view = std::is_same<decltype(result), std::unique_ptr<views::View>>::value;
    EXPECT_TRUE(result_is_view);

    const views::GameNone* game_none = dynamic_cast<views::GameNone*>(result.get());
    EXPECT_TRUE(game_none != nullptr);
}

}
