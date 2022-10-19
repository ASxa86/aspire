#include <aspire/Node.h>
#include <gtest/gtest.h>

TEST(Node, name)
{
	aspire::Node node;
	node.setName("ASPIRE");
	EXPECT_EQ("ASPIRE", node.getName());
}
