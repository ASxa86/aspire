#include <aspire/Node.h>
#include <gtest/gtest.h>

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
