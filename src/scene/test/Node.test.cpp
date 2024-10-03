#include <aspire/scene/Node.h>
#include <gtest/gtest.h>

using aspire::scene::Node;

TEST(Node, insertChildAfter)
{
	Node node;

	node.addChild(std::make_unique<Node>());
	ASSERT_FALSE(std::empty(node.children()));

	auto test = std::make_unique<Node>();
	auto* testPtr = test.get();
	node.insertChildAfter(node.children().back().get(), std::move(test));
	ASSERT_EQ(std::size(node.children()), 2U);
	EXPECT_EQ(node.children()[1].get(), testPtr);
}

TEST(Node, insertChildBefore)
{
	Node node;

	node.addChild(std::make_unique<Node>());
	ASSERT_FALSE(std::empty(node.children()));

	auto test = std::make_unique<Node>();
	auto* testPtr = test.get();
	node.insertChildBefore(node.children().back().get(), std::move(test));
	ASSERT_EQ(std::size(node.children()), 2U);
	EXPECT_EQ(node.children()[0].get(), testPtr);
}

TEST(Node, remove)
{
	Node node;

	auto child = std::make_unique<Node>();
	auto* testPtr = child.get();
	node.addChild(std::move(child));
	EXPECT_FALSE(std::empty(node.children()));

	testPtr->remove();
	EXPECT_TRUE(std::empty(node.children()));
}

TEST(Node, dirty)
{
	Node node;

	aspire::core::EnumMask<Node::Dirty> test{};

	node.onDirty([&test](auto*, auto dirty) { test = dirty; });

	node.dirty<Node::Dirty::Geometry>();
	EXPECT_TRUE(test.test(Node::Dirty::Geometry));

	node.dirty<Node::Dirty::Matrix>();
	EXPECT_TRUE(test.test(Node::Dirty::Matrix));

}
