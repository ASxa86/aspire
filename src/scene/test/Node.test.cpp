#include <aspire/scene/Node.h>
#include <gtest/gtest.h>

using aspire::scene::Node;

TEST(Node, x)
{
	Node Node;
	Node.setX(std::numeric_limits<int>::max());
	EXPECT_EQ(Node.getX(), std::numeric_limits<int>::max());
}

TEST(Node, y)
{
	Node Node;
	Node.setY(std::numeric_limits<int>::max());
	EXPECT_EQ(Node.getY(), std::numeric_limits<int>::max());
}

TEST(Node, width)
{
	Node Node;
	Node.setWidth(std::numeric_limits<int>::max());
	EXPECT_EQ(Node.getWidth(), std::numeric_limits<int>::max());
}

TEST(Node, height)
{
	Node Node;
	Node.setHeight(std::numeric_limits<int>::max());
	EXPECT_EQ(Node.getHeight(), std::numeric_limits<int>::max());
}