#include <aspire/scene/Rectangle.h>
#include <gtest/gtest.h>

using aspire::scene::Rectangle;

TEST(Rectangle, size)
{
	Rectangle node;
	node.setSize({std::numeric_limits<float>::max(), std::numeric_limits<float>::max()});
	EXPECT_FLOAT_EQ(node.getSize().x, std::numeric_limits<float>::max());
	EXPECT_FLOAT_EQ(node.getSize().y, std::numeric_limits<float>::max());
}
