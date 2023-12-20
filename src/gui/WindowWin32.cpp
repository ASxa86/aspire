#include <aspire/gui/Window.h>

#include <aspire/core/Kernel.h>
#include <aspire/core/PimplImpl.h>
#include <aspire/gui/EventMouse.h>
#include "ContextWin32.h"

using aspire::Window;

struct Window::Impl
{
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		auto* window = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

		if(window == nullptr)
		{
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}

		auto* kernel = window->getParent<Kernel>();

		if(kernel == nullptr)
		{
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}

		std::unique_ptr<aspire::Event> event;

		switch(uMsg)
		{
			case WM_MOVE:
				break;

			case WM_LBUTTONDOWN:
			{
				auto eventMouse = std::make_unique<EventMouse>(Event::Type::MousePressed);

				auto pos = eventMouse->getPosition();
				pos.setX(static_cast<std::int16_t>(LOWORD(lParam)));
				pos.setY(static_cast<std::int16_t>(HIWORD(lParam)));
				eventMouse->setButton(EventMouse::Button::Left);
				event = std::move(eventMouse);
				break;
			}

			case WM_LBUTTONUP:
			{
				auto eventMouse = std::make_unique<EventMouse>(Event::Type::MouseReleased);

				auto pos = eventMouse->getPosition();
				pos.setX(static_cast<std::int16_t>(LOWORD(lParam)));
				pos.setY(static_cast<std::int16_t>(HIWORD(lParam)));
				eventMouse->setButton(EventMouse::Button::Left);
				event = std::move(eventMouse);
				break;
			}

			case WM_MBUTTONDOWN:
			{
				auto eventMouse = std::make_unique<EventMouse>(Event::Type::MousePressed);

				auto pos = eventMouse->getPosition();
				pos.setX(static_cast<std::int16_t>(LOWORD(lParam)));
				pos.setY(static_cast<std::int16_t>(HIWORD(lParam)));
				eventMouse->setButton(EventMouse::Button::Middle);
				event = std::move(eventMouse);
				break;
			}

			case WM_MBUTTONUP:
			{
				auto eventMouse = std::make_unique<EventMouse>(Event::Type::MouseReleased);

				auto pos = eventMouse->getPosition();
				pos.setX(static_cast<std::int16_t>(LOWORD(lParam)));
				pos.setY(static_cast<std::int16_t>(HIWORD(lParam)));
				eventMouse->setButton(EventMouse::Button::Middle);
				event = std::move(eventMouse);
				break;
			}

			case WM_RBUTTONDOWN:
			{
				auto eventMouse = std::make_unique<EventMouse>(Event::Type::MousePressed);

				auto pos = eventMouse->getPosition();
				pos.setX(static_cast<std::int16_t>(LOWORD(lParam)));
				pos.setY(static_cast<std::int16_t>(HIWORD(lParam)));
				eventMouse->setButton(EventMouse::Button::Right);
				event = std::move(eventMouse);
				break;
			}

			case WM_RBUTTONUP:
			{
				auto eventMouse = std::make_unique<EventMouse>(Event::Type::MouseReleased);

				auto pos = eventMouse->getPosition();
				pos.setX(static_cast<std::int16_t>(LOWORD(lParam)));
				pos.setY(static_cast<std::int16_t>(HIWORD(lParam)));
				eventMouse->setButton(EventMouse::Button::Right);
				event = std::move(eventMouse);
				break;
			}

			case WM_CLOSE:
				kernel->quit();
				break;

			default:
				break;
		}

		kernel->event(event.get());

		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	~Impl()
	{
		this->destroy();
	}

	void destroy()
	{
		DestroyWindow(this->handle);
		UnregisterClass(this->className, this->hInstance);
		this->handle = 0;
	}

	HINSTANCE hInstance{GetModuleHandle(nullptr)};
	HWND handle{};
	WNDCLASS wc{};
	const char* className{"AspireWindow"};
	std::unique_ptr<ContextWin32> context;
};

Window::Window()
{
	Object::connect(this, &Object::initialized, this, [this] { this->onInitialized(); });
}

auto Window::onInitialized() -> void
{
	this->pimpl->wc.lpfnWndProc = &Impl::WindowProc;
	this->pimpl->wc.hInstance = this->pimpl->hInstance;
	this->pimpl->wc.lpszClassName = this->pimpl->className;

	if(RegisterClass(&this->pimpl->wc) == 0)
	{
		// error
		return;
	}

	this->pimpl->handle = CreateWindowEx(0,								 //	Optional Styles
										 this->pimpl->className,		 // ClassName
										 this->getTitle().data(), // Window Title
										 WS_OVERLAPPEDWINDOW,			 // Window Style
										 this->getX(),					 // Position X
										 this->getY(),					 // Position Y
										 this->getWidth(),				 // Size Width
										 this->getHeight(),				 // Size Height
										 nullptr,						 //
										 nullptr,						 //
										 this->pimpl->hInstance,		 // Application Handle
										 nullptr						 //
	);

	SetWindowLongPtr(this->pimpl->handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	this->pimpl->context = std::make_unique<ContextWin32>(this->pimpl->handle);
	this->pimpl->context->setSurface(this->getSurface());
	this->pimpl->context->create();

	ShowWindow(this->pimpl->handle, SW_SHOW);

	auto* kernel = this->getParent<Kernel>();

	if(kernel == nullptr)
	{
		return;
	}

	Object::connect(kernel, &Kernel::frame, this, [this] { this->processEvents(); });
}

auto Window::processEvents() -> void
{
	MSG msg{};

	while(PeekMessage(&msg, this->pimpl->handle, 0, 0, PM_REMOVE) != 0)
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
}
