#include <aspire/core/Point.h>
#include <gtest/gtest.h>

using aspire::core::Point;

TEST(Point, constructor)
{
	Point point{std::numeric_limits<int>::max(), std::numeric_limits<int>::min()};
	EXPECT_EQ(point.getX(), std::numeric_limits<int>::max());
	EXPECT_EQ(point.getY(), std::numeric_limits<int>::min());
}
