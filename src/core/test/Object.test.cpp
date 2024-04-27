#include <aspire/core/Object.h>
#include <gtest/gtest.h>

using aspire::core::Object;

TEST(Object, name)
{
	Object object;
	object.setName("object");
	EXPECT_EQ(object.getName(), "object");

	object.setName("");
	EXPECT_EQ(object.getName(), "");
	EXPECT_TRUE(object.getName().empty());
}

TEST(Object, remove)
{
	Object parent;
	auto child = std::make_unique<Object>();
	auto* childObject = child.get();
	parent.addChild(std::move(child));
	EXPECT_EQ(childObject->getParent(), &parent);
	EXPECT_FALSE(parent.getChildren().empty());

	child = childObject->remove();
	ASSERT_NE(child, nullptr);
	EXPECT_EQ(child->getParent(), nullptr);
	EXPECT_TRUE(parent.getChildren().empty());
}
