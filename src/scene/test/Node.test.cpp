#include <aspire/scene/Node.h>
#include <gtest/gtest.h>

using aspire::scene::Node;

TEST(Node, addChild)
{
	Node node;

	node.addChild(std::make_unique<Node>());
	EXPECT_FALSE(node.getChildren().empty());
}

TEST(Node, remove)
{
	Node node;

	auto child = std::make_unique<Node>();
	auto* childNode = child.get();
	node.addChild(std::move(child));
	EXPECT_FALSE(node.getChildren().empty());
	EXPECT_EQ(childNode->getParent(), &node);

	child = childNode->remove();
	ASSERT_NE(child, nullptr);
	EXPECT_EQ(child->getParent(), nullptr);
	EXPECT_TRUE(node.getChildren().empty());
}
