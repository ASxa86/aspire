#include <aspire/graphics/Window.h>

#define SDL_ENABLE_OLD_NAMES
#include <SDL3/SDL.h>
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
	Impl(int w, int h) : width{static_cast<Uint32>(w)}, height{static_cast<Uint32>(h)}
	{
	}

	std::function<void(EventWindow)> onEventWindow{[](auto) {}};
	SDL_Window* window{};
	SDL_GPUDevice* device{};
	SDL_GPUCommandBuffer* command{};
	SDL_GPUTexture* swapchain{};
	SDL_GPURenderPass* renderPass{};
	Uint32 width{};
	Uint32 height{};
	bool open{false};
};

Window::Window(int width, int height, aspire::core::EnumMask<Hints> hints) : pimpl{width, height}
{
	this->pimpl->open = SDL_Init(SDL_INIT_VIDEO);
	this->pimpl->device = SDL_CreateGPUDevice(SDL_GPUShaderFormat{SDL_GPU_SHADERFORMAT_SPIRV}, false, nullptr);

	auto sdlHints = SDL_WindowFlags{};
	sdlHints |= hints.test(Window::Hints::Resizeable) == true ? SDL_WINDOW_RESIZABLE : 0;
	sdlHints |= hints.test(Window::Hints::Vulkan) == true ? SDL_WINDOW_VULKAN : 0;
	sdlHints |= hints.test(Window::Hints::Borderless) == true ? SDL_WINDOW_BORDERLESS : 0;
	sdlHints |= hints.test(Window::Hints::OpenGL) == true ? SDL_WINDOW_OPENGL : 0;

	this->pimpl->window = SDL_CreateWindow("aspire", this->pimpl->width, this->pimpl->height, sdlHints);
	this->pimpl->open &= SDL_ClaimWindowForGPUDevice(this->pimpl->device, this->pimpl->window);
}

Window::~Window()
{
	SDL_ReleaseWindowFromGPUDevice(this->pimpl->device, this->pimpl->window);
	SDL_DestroyWindow(this->pimpl->window);
	SDL_DestroyGPUDevice(this->pimpl->device);
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

auto Window::clear(Color x) noexcept -> void
{
	this->pimpl->command = SDL_AcquireGPUCommandBuffer(this->pimpl->device);
	this->pimpl->open &=
		SDL_AcquireGPUSwapchainTexture(this->pimpl->command, this->pimpl->window, &this->pimpl->swapchain, &this->pimpl->width, &this->pimpl->height);

	SDL_GPUColorTargetInfo color{};
	color.clear_color = SDL_FColor{.r = x.red, .g = x.green, .b = x.blue, .a = x.alpha};
	color.load_op = SDL_GPU_LOADOP_CLEAR;
	color.store_op = SDL_GPU_STOREOP_STORE;
	color.texture = this->pimpl->swapchain;

	this->pimpl->renderPass = SDL_BeginGPURenderPass(this->pimpl->command, &color, 1, nullptr);
}

// auto Window::draw(const Drawable& x) noexcept -> void
//{
//	x.draw(*this);
// }

auto Window::draw(const std::vector<Vertex>& x) -> void
{
	if(std::empty(x) == true || this->pimpl->renderPass == nullptr)
	{
		return;
	}

	SDL_GPUViewport viewport{};
	viewport.x = 0;
	viewport.y = 0;
	viewport.w = static_cast<float>(this->pimpl->width);
	viewport.h = static_cast<float>(this->pimpl->height);
	viewport.min_depth = 0.0F;
	viewport.max_depth = 1.0F;
	SDL_SetGPUViewport(this->pimpl->renderPass, &viewport);
}

auto Window::display() noexcept -> void
{
	SDL_EndGPURenderPass(this->pimpl->renderPass);
	SDL_SubmitGPUCommandBuffer(this->pimpl->command);
}

auto Window::processEvents() const noexcept -> void
{
	std::optional<Event> event;

	SDL_Event sdlEvent{};
	while(SDL_PollEvent(&sdlEvent) != 0)
	{
		switch(sdlEvent.type)
		{
			case SDL_EventType::SDL_EVENT_WINDOW_CLOSE_REQUESTED:
			{
				EventWindow evtWindow{.type = EventWindow::Type::Close};
				event = evtWindow;

				break;
			}

			case SDL_EventType::SDL_EVENT_QUIT:
			{
				EventWindow evtWindow{.type = EventWindow::Type::Close};
				event = evtWindow;
				break;
			}

			default:
				break;
		}

		if(event.has_value() == true)
		{
			std::visit(EventHandler{[](auto) {}, this->pimpl->onEventWindow}, event.value());
		}
	}
}

auto Window::onEvent(std::function<void(EventWindow)> x) noexcept -> void
{
	this->pimpl->onEventWindow = std::move(x);
}
