#include <aspire/graphics/Window.h>

#include <SDL2/SDL.h>
#include <aspire/core/PimplImpl.h>

using aspire::Window;

namespace
{
	template <class... Ts>
	struct EventHandler : Ts...
	{
		using Ts::operator()...;
	};

}

struct Window::Impl
{
	std::function<void(EventWindow)> onEventWindow{[](auto) {}};
	SDL_Window* window{};
	SDL_Renderer* renderer{};
	bool open{false};
};

Window::Window()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	this->pimpl->window = SDL_CreateWindow("aspire", 80, 80, 1280, 720, 0);
	this->pimpl->renderer = SDL_CreateRenderer(this->pimpl->window, -1, 0);
	this->pimpl->open = this->pimpl->window != nullptr && this->pimpl->renderer != nullptr;
}

Window::~Window()
{
	SDL_DestroyWindow(this->pimpl->window);
	SDL_Quit();
}

auto Window::open() const noexcept -> bool
{
	return this->pimpl->open;
}

auto Window::close() noexcept -> void
{
	this->pimpl->open = false;
}

auto Window::clear(Color x) const noexcept -> void
{
	constexpr auto u8max = std::numeric_limits<Uint8>::max();
	const auto red = static_cast<Uint8>(x.red * u8max);
	const auto green = static_cast<Uint8>(x.green * u8max);
	const auto blue = static_cast<Uint8>(x.blue * u8max);
	const auto alpha = static_cast<Uint8>(x.alpha * u8max);

	SDL_SetRenderDrawColor(this->pimpl->renderer, red, green, blue, alpha);
	SDL_RenderClear(this->pimpl->renderer);
}

// auto Window::draw(const Drawable& x) noexcept -> void
//{
//	x.draw(*this);
// }

auto Window::draw(const std::vector<Vertex>& x) -> void
{
	if(std::empty(x) == true)
	{
		return;
	}

	// Playing a dangerous game here...
	const auto* vertices = reinterpret_cast<const SDL_Vertex*>(x.data());
	SDL_RenderSetScale(this->pimpl->renderer, 100.0F, 100.0F);
	SDL_RenderGeometry(this->pimpl->renderer, nullptr, vertices, static_cast<int>(x.size()), nullptr, 0);
}

auto Window::display() const noexcept -> void
{
	SDL_RenderPresent(this->pimpl->renderer);
}

auto Window::processEvents() const noexcept -> void
{
	Event event;
	SDL_Event sdlEvent{};
	while(SDL_PollEvent(&sdlEvent) != 0)
	{
		switch(sdlEvent.type)
		{
			case SDL_WINDOWEVENT:
			{
				EventWindow evtWindow;

				switch(sdlEvent.window.type)
				{
					case SDL_WINDOWEVENT_CLOSE:
					{
						evtWindow.type = EventWindow::Type::Close;
						event = evtWindow;
						break;
					}

					default:
						break;
				}

				break;
			}

			case SDL_QUIT:
			{
				EventWindow evtWindow;
				evtWindow.type = EventWindow::Type::Close;
				event = evtWindow;
				break;
			}

			default:
				break;
		}

		std::visit(EventHandler{[](auto) {}, this->pimpl->onEventWindow}, event);
	}
}

auto Window::onEvent(std::function<void(EventWindow)> x) noexcept -> void
{
	this->pimpl->onEventWindow = std::move(x);
}
