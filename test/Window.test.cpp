#include <aspire/Node.h>
#include <aspire/Window.h>
#include <gtest/gtest.h>

TEST(Graphics_Window, test)
{
	aspire::Traits traits;
	traits.title = "Window.test.cpp";
	aspire::Window window{traits};

	aspire::Node node{};

	window.setNode(node);

	window.run();
}
