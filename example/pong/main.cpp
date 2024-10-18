#include <aspire/graphics/Window.h>

using aspire::Window;

auto main() -> int
{
	Window window;

	window.onEvent(
		[&window](aspire::EventWindow x)
		{
			if(x.type == aspire::EventWindow::Type::Close)
			{
				window.close();
			}
		});

	while(window.open() == true)
	{
		window.processEvents();
		window.clear(aspire::Color::White);
		window.display();
	}

	return 0;
}