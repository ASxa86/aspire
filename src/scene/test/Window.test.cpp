#include <aspire/scene/Window.h>
#include <gtest/gtest.h>

using aspire::scene::Node;
using aspire::scene::Window;

TEST(Window, node)
{
	Window window;

	auto node = std::make_unique<Node>();
	auto* n = node.get();
	window.setRootNode(std::move(node));
	EXPECT_EQ(window.getRootNode(), n);
}