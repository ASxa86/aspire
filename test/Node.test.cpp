#include <aspire/Node.h>
#include <gtest/gtest.h>

namespace
{
	class Node1 : public aspire::Node
	{
	public:
		using aspire::Node::Node;
	};

	class Node2 : public aspire::Node
	{
	public:
		using aspire::Node::Node;
	};

	class Node3 : public aspire::Node
	{
	public:
		using aspire::Node::Node;
	};
}

TEST(Node, name)
{
	aspire::Node node;
	node.setName("ASPIRE");
	EXPECT_EQ("ASPIRE", node.getName());
}

TEST(Node, addChild)
{
	aspire::Node node;

	node.addChild(std::make_unique<aspire::Node>());
	EXPECT_EQ(node.getChildren().size(), 1);
}

TEST(Node, getChildren)
{
	aspire::Node node;
	node.addChild<Node1>("one");
	node.addChild<Node2>("two");
	node.addChild<Node3>("three");

	EXPECT_EQ(node.getChildren<Node1>().size(), 1);
	EXPECT_EQ(node.getChildren<Node2>().size(), 1);
	EXPECT_EQ(node.getChildren<Node3>().size(), 1);
}
