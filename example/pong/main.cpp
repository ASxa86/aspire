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

	std::vector<aspire::Vertex> vertices;

	vertices.emplace_back(aspire::Vertex{.position = {.x = 0.0F, .y = 0.0F}, .color = aspire::Color::White});
	vertices.emplace_back(aspire::Vertex{.position = {.x = 0.0F, .y = 10.0F}, .color = aspire::Color::White});
	vertices.emplace_back(aspire::Vertex{.position = {.x = 10.0F, .y = 0.0F}, .color = aspire::Color::White});

	vertices.emplace_back(aspire::Vertex{.position = {.x = 0.0F, .y = 10.0F}, .color = aspire::Color::White});
	vertices.emplace_back(aspire::Vertex{.position = {.x = 10.0F, .y = 10.0F}, .color = aspire::Color::White});
	vertices.emplace_back(aspire::Vertex{.position = {.x = 10.0F, .y = 0.0F}, .color = aspire::Color::White});

	while(window.open() == true)
	{
		window.processEvents();
		window.clear();
		window.draw(vertices);
		window.display();
	}

	return 0;
}