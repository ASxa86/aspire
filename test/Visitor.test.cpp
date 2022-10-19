#include <aspire/Node.h>
#include <gtest/gtest.h>

TEST(Visitor, visit)
{
	aspire::Visitor visitor;

	aspire::Node node;
	node.addChild(std::make_unique<aspire::Node>("one"));
	node.addChild(std::make_unique<aspire::Node>("two"));
	node.addChild(std::make_unique<aspire::Node>("three"));

	node.accept(visitor);
}
