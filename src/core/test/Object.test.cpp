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
	parent.addChild(std::make_unique<Object>());
	ASSERT_FALSE(parent.getChildren().empty());
	parent.getChildren()[0]->remove();
	EXPECT_TRUE(parent.getChildren().empty());
}