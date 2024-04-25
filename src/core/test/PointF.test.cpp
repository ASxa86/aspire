#include <aspire/core/PointF.h>
#include <gtest/gtest.h>

using aspire::core::PointF;

TEST(PointF, constructor)
{
	PointF point{std::numeric_limits<float>::max(), std::numeric_limits<float>::min()};
	EXPECT_EQ(point.getX(), std::numeric_limits<float>::max());
	EXPECT_EQ(point.getY(), std::numeric_limits<float>::min());
}
