#include <aspire/Meters.h>
#include <gtest/gtest.h>

using aspire::Meters;

TEST(Meters, toDouble)
{
	Meters meters{std::numeric_limits<double>::max()};
	EXPECT_DOUBLE_EQ(meters.toDouble(), std::numeric_limits<double>::max());
}
