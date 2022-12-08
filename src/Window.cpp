#include <EGL/egl.h>
#include <aspire/Node.h>
#include <aspire/Window.h>
#include <glad/glad.h>

// Include glfw AFTER glad to prevent multiple gl.h inclusion errors.
#include <GLFW/glfw3.h>
#include <array>

using aspire::Window;

namespace
{
	void CallbackKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		aspire::EventKeyboard event;
		event.type = action == GLFW_PRESS ? aspire::EventKeyboard::Type::Pressed : aspire::EventKeyboard::Type::Released;

		switch(key)
		{
			case GLFW_KEY_0:
				event.key = aspire::EventKeyboard::Key::Num0;
				break;

			case GLFW_KEY_1:
				event.key = aspire::EventKeyboard::Key::Num1;
				break;

			default:
				break;
		}

		if((mods & GLFW_MOD_ALT) == GLFW_MOD_ALT)
		{
			event.modifier.add(aspire::EventKeyboard::Modifier::Alt);
		}

		if((mods & GLFW_MOD_CONTROL) == GLFW_MOD_CONTROL)
		{
			event.modifier.add(aspire::EventKeyboard::Modifier::Control);
		}

		if((mods & GLFW_MOD_SHIFT) == GLFW_MOD_SHIFT)
		{
			event.modifier.add(aspire::EventKeyboard::Modifier::Shift);
		}

		if((mods & GLFW_MOD_SUPER) == GLFW_MOD_SUPER)
		{
			event.modifier.add(aspire::EventKeyboard::Modifier::Super);
		}

		const auto pointer = glfwGetWindowUserPointer(window);
		const auto events = static_cast<std::vector<aspire::Event>*>(pointer);
		events->emplace_back(std::move(event));
	}

	void CallbackMouseMove(GLFWwindow* window, double xpos, double ypos)
	{
		aspire::EventMouse event;
		event.type = aspire::EventMouse::Type::Moved;
		event.x = static_cast<float>(xpos);
		event.y = static_cast<float>(ypos);

		const auto pointer = glfwGetWindowUserPointer(window);
		const auto events = static_cast<std::vector<aspire::Event>*>(pointer);
		events->emplace_back(std::move(event));
	}

	void CallbackMouseEnter(GLFWwindow* window, int entered)
	{
		double xpos{};
		double ypos{};
		glfwGetCursorPos(window, &xpos, &ypos);

		aspire::EventMouse event;
		event.type = aspire::EventMouse::Type::Entered;
		event.x = static_cast<float>(xpos);
		event.y = static_cast<float>(ypos);

		const auto pointer = glfwGetWindowUserPointer(window);
		const auto events = static_cast<std::vector<aspire::Event>*>(pointer);
		events->emplace_back(std::move(event));
	}

	void CallbackMouseButton(GLFWwindow* window, int button, int action, int mods)
	{
		double xpos{};
		double ypos{};
		glfwGetCursorPos(window, &xpos, &ypos);

		aspire::EventMouse event;
		event.type = action == GLFW_PRESS ? aspire::EventMouse::Type::Pressed : aspire::EventMouse::Type::Released;
		event.x = static_cast<float>(xpos);
		event.y = static_cast<float>(ypos);

		if((mods & GLFW_MOD_ALT) == GLFW_MOD_ALT)
		{
			event.modifier.add(aspire::EventMouse::Modifier::Alt);
		}

		if((mods & GLFW_MOD_CONTROL) == GLFW_MOD_CONTROL)
		{
			event.modifier.add(aspire::EventMouse::Modifier::Control);
		}

		if((mods & GLFW_MOD_SHIFT) == GLFW_MOD_SHIFT)
		{
			event.modifier.add(aspire::EventMouse::Modifier::Shift);
		}

		if((mods & GLFW_MOD_SUPER) == GLFW_MOD_SUPER)
		{
			event.modifier.add(aspire::EventMouse::Modifier::Super);
		}

		const auto pointer = glfwGetWindowUserPointer(window);
		const auto events = static_cast<std::vector<aspire::Event>*>(pointer);
		events->emplace_back(std::move(event));
	}

	void CallbackMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
	{
		double xpos{};
		double ypos{};
		glfwGetCursorPos(window, &xpos, &ypos);

		aspire::EventMouse event;
		event.type = aspire::EventMouse::Type::Scrolled;
		event.x = static_cast<float>(xpos);
		event.y = static_cast<float>(ypos);
		event.scrollX = static_cast<float>(xoffset);
		event.scrollY = static_cast<float>(yoffset);

		const auto pointer = glfwGetWindowUserPointer(window);
		const auto events = static_cast<std::vector<aspire::Event>*>(pointer);
		events->emplace_back(std::move(event));
	}
}

Window::Window(aspire::Traits x) : traits{x}
{
	this->glfwInitialized = glfwInit() == GLFW_TRUE;

	if(this->glfwInitialized == true)
	{
		glfwWindowHint(GLFW_RED_BITS, this->traits.bitsRed);
		glfwWindowHint(GLFW_GREEN_BITS, this->traits.bitsGreen);
		glfwWindowHint(GLFW_BLUE_BITS, this->traits.bitsBlue);
		glfwWindowHint(GLFW_ALPHA_BITS, this->traits.bitsAlpha);
		glfwWindowHint(GLFW_VERSION_MAJOR, this->traits.major);
		glfwWindowHint(GLFW_VERSION_MINOR, this->traits.minor);

		this->window = glfwCreateWindow(this->traits.width, this->traits.height, this->traits.title.c_str(), nullptr, nullptr);
		this->makeCurrent();

		this->gladInitialized = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == GL_TRUE;

		glfwSetWindowUserPointer(this->window, &this->events);
		glfwSetKeyCallback(this->window, CallbackKeyboard);
		glfwSetMouseButtonCallback(this->window, CallbackMouseButton);
		glfwSetScrollCallback(this->window, CallbackMouseScroll);
		glfwSetCursorPosCallback(this->window, CallbackMouseMove);
		glfwSetCursorEnterCallback(this->window, CallbackMouseEnter);

		// Ensure context is current prior to constructing the default state of the context.
		this->state = std::make_unique<aspire::State>();
	}
}

Window::~Window()
{
	if(this->glfwInitialized == true)
	{
		glfwDestroyWindow(this->window);
		glfwTerminate();
	}
}

auto Window::makeCurrent() -> void
{
	glfwMakeContextCurrent(this->window);
}

auto Window::makeRelease() -> void
{
	glfwMakeContextCurrent(nullptr);
}

auto Window::clear() -> void
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(this->clearColor.r, this->clearColor.g, this->clearColor.b, this->clearColor.a);
}

auto Window::swapBuffers() -> void
{
	glfwSwapBuffers(this->window);
}

auto Window::open() const -> bool
{
	return glfwWindowShouldClose(this->window) == GLFW_FALSE;
}

auto Window::run() -> int
{
	auto start = std::chrono::steady_clock::now();

	while(this->open() == true)
	{
		const auto stop = std::chrono::steady_clock::now();
		this->elapsed = stop - start;
		start = stop;

		this->frame(this->elapsed);
	}

	return EXIT_SUCCESS;
}

auto Window::frame(std::chrono::steady_clock::duration x) -> void
{
	this->frameEvent();
	this->frameUpdate();
	// frameCull();
	//
	this->makeCurrent();
	this->clear();

	// framePreRender();
	this->frameDraw();
	// framePostRender();

	this->swapBuffers();
	this->makeRelease();
}

auto Window::frameEvent() -> void
{
	glfwPollEvents();

	if(this->root != nullptr)
	{
		for(auto&& event : this->events)
		{
			this->root->event(event);
		}
	}

	this->events.clear();
}

auto Window::frameUpdate() -> void
{
	if(this->root != nullptr)
	{
		this->root->update();
	}
}

auto Window::frameDraw() -> void
{
	if(this->root != nullptr)
	{
		this->root->draw(*this->state);
	}
}

auto Window::setNode(Node& x) -> void
{
	this->root = &x;
}

auto Window::getNode() const -> Node*
{
	return this->root;
}
