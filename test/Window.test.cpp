#include <aspire/Window.h>
#include <gtest/gtest.h>

TEST(Graphics_Window, test)
{
	aspire::Window::Traits traits;
	traits.title = "Window.test.cpp";
	aspire::Window window{traits};

	window.run();
}
