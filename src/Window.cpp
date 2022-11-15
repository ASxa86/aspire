#include <aspire/Node.h>
#include <aspire/Window.h>
#include <glad/glad.h>
// Include glfw AFTER glad to prevent multiple gl.h inclusion errors.
#include <GLFW/glfw3.h>

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
		this->window = glfwCreateWindow(this->traits.width, this->traits.height, this->traits.title.c_str(), nullptr, nullptr);
		this->gladInitialized = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) == GL_TRUE;

		glfwSetWindowUserPointer(this->window, &this->events);
		glfwSetKeyCallback(this->window, CallbackKeyboard);
		glfwSetMouseButtonCallback(this->window, CallbackMouseButton);
		glfwSetScrollCallback(this->window, CallbackMouseScroll);
		glfwSetCursorPosCallback(this->window, CallbackMouseMove);
		glfwSetCursorEnterCallback(this->window, CallbackMouseEnter);
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
	// framePreRender();
	this->frameDraw();
	// framePostRender();
}

auto Window::frameEvent() -> void
{
	glfwPollEvents();

	if(this->node != nullptr)
	{
		for(auto&& event : this->events)
		{
			this->node->event(event);
		}
	}

	this->events.clear();
}

auto Window::frameUpdate() -> void
{
	if(this->node != nullptr)
	{
		this->node->update();
	}
}

auto Window::frameDraw() -> void
{
	if(this->node != nullptr)
	{
		this->node->draw();
	}
}

auto Window::setNode(Node& x) -> void
{
	this->node = &x;
}

auto Window::getNode() const -> Node*
{
	return this->node;
}
