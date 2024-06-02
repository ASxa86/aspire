#include <aspire/render/Window.h>
#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <aspire/core/PimplImpl.h>
#include <array>
#include <vector>

using aspire::render::EventMouse;
using aspire::render::EventWindow;
using aspire::render::Window;

namespace
{
	template <class... Ts>
	struct EventHandler : Ts...
	{
		using Ts::operator()...;
	};

	auto GetWindow(GLFWwindow* x) -> Window*
	{
		// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
		return reinterpret_cast<Window*>(glfwGetWindowUserPointer(x));
	}

	auto CallbackWindowClose(GLFWwindow* glfw) -> void
	{
		auto* window = GetWindow(glfw);

		EventWindow event;
		event.type = EventWindow::Type::Close;
		window->addEvent(event);
	}

	auto CallbackWindowResize(GLFWwindow* glfw, int width, int height) -> void
	{
		auto* window = GetWindow(glfw);

		EventWindow event;
		event.type = EventWindow::Type::Resize;
		event.width = width;
		event.height = height;
		window->addEvent(event);
	}

	// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
	auto CallbackMousePos(GLFWwindow* glfw, double x, double y) -> void
	{
		auto* window = GetWindow(glfw);

		EventMouse event;
		event.x = x;
		event.y = y;
		event.type = EventMouse::Type::Move;
		window->addEvent(event);
	}

	// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
	auto CallbackMouseButton(GLFWwindow* glfw, int button, int action, int /*unused*/) -> void
	{
		auto* window = GetWindow(glfw);

		double x{};
		double y{};
		glfwGetCursorPos(glfw, &x, &y);

		EventMouse event;
		event.x = x;
		event.y = y;

		switch(button)
		{
			case GLFW_MOUSE_BUTTON_LEFT:
				event.button = EventMouse::Button::Left;
				break;

			case GLFW_MOUSE_BUTTON_MIDDLE:
				event.button = EventMouse::Button::Middle;
				break;

			case GLFW_MOUSE_BUTTON_RIGHT:
				event.button = EventMouse::Button::Right;
				break;

			default:
				break;
		}

		switch(action)
		{
			case GLFW_PRESS:
				event.type = EventMouse::Type::Press;
				break;

			case GLFW_RELEASE:
				event.type = EventMouse::Type::Release;
				break;

			default:
				break;
		}

		window->addEvent(event);
	}
}

struct Window::Impl
{
	GLFWwindow* window{};

	std::vector<Event> events;

	// Default initialize event handlers to do nothing. This is being done to save an extra if check
	// on valid functions everytime the events get processed.
	std::function<void(EventWindow)> handleEventWindow{[](auto) {}};
	std::function<void(EventMouse)> handleEventMouse{[](auto) {}};

	std::string title;
	glm::vec4 clearColor{0.2f, 0.3f, 0.3f, 1.0f};
	int x{};
	int y{};
	int width{};
	int height{};
	bool valid{false};
};

Window::Window() noexcept = default;
Window::~Window() = default;

auto Window::setTitle(std::string_view x) -> void
{
	this->pimpl->title = x;
}

auto Window::getTitle() const -> std::string_view
{
	return this->pimpl->title;
}

auto Window::setX(int x) noexcept -> void
{
	this->pimpl->x = x;
}

auto Window::getX() const noexcept -> int
{
	return this->pimpl->x;
}

auto Window::setY(int x) noexcept -> void
{
	this->pimpl->y = x;
}

auto Window::getY() const noexcept -> int
{
	return this->pimpl->y;
}

auto Window::setHeight(int x) noexcept -> void
{
	this->pimpl->height = x;
}

auto Window::getHeight() const noexcept -> int
{
	return this->pimpl->height;
}

auto Window::setWidth(int x) noexcept -> void
{
	this->pimpl->width = x;
}

auto Window::getWidth() const noexcept -> int
{
	return this->pimpl->width;
}

auto Window::setClearColor(glm::vec4 x) noexcept -> void
{
	this->pimpl->clearColor = x;
}

auto Window::getClearColor() const noexcept -> glm::vec4
{
	return this->pimpl->clearColor;
}

auto Window::addEvent(Event x) -> void
{
	this->pimpl->events.emplace_back(x);
}

auto Window::handleEvent(std::function<void(EventWindow)> x) -> void
{
	this->pimpl->handleEventWindow = std::move(x);
}

auto Window::handleEvent(std::function<void(EventMouse)> x) -> void
{
	this->pimpl->handleEventMouse = std::move(x);
}

auto Window::create() -> void
{
	if(glfwInit() == GLFW_FALSE)
	{
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->pimpl->window = glfwCreateWindow(this->pimpl->width, this->pimpl->height, this->pimpl->title.c_str(), nullptr, nullptr);

	if(this->pimpl->window == nullptr)
	{
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(this->pimpl->window);

	if(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == GL_FALSE)
	{
		return;
	}

	glfwSetWindowUserPointer(this->pimpl->window, this);
	glfwSetWindowCloseCallback(this->pimpl->window, &CallbackWindowClose);
	glfwSetWindowSizeCallback(this->pimpl->window, &CallbackWindowResize);
	glfwSetCursorPosCallback(this->pimpl->window, &CallbackMousePos);
	glfwSetMouseButtonCallback(this->pimpl->window, &CallbackMouseButton);

	this->pimpl->valid = this->pimpl->window != nullptr;

	// Release the context to give the Window::frame() invoker the opportunity to render on a different thread.
	glfwMakeContextCurrent(nullptr);
}

auto Window::destroy() -> void
{
	if(this->valid())
	{
		glfwDestroyWindow(this->pimpl->window);
	}

	glfwTerminate();
}

auto Window::valid() noexcept -> bool
{
	return this->pimpl->valid;
}

auto Window::frame() -> void
{
	// Process events
	for(auto event : this->pimpl->events)
	{
		std::visit(EventHandler{[](auto) {}, this->pimpl->handleEventWindow, this->pimpl->handleEventMouse}, event);
	}

	this->pimpl->events.clear();

	glfwMakeContextCurrent(this->pimpl->window);

	glClearColor(this->pimpl->clearColor.r, this->pimpl->clearColor.g, this->pimpl->clearColor.b, this->pimpl->clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT);

	// sort command buffer? Sort geometry by shader requirements?
	// 
	//
	// Command Buffer
	// Loop over queued commands, update buffer data, texture data, etc...
	// queued commands may consist of glViewport, glDrawyArrays, glUseProgram, etc...
	int fbWidth{};
	int fbHeight{};
	glfwGetFramebufferSize(this->pimpl->window, &fbWidth, &fbHeight);
	glViewport(0, 0, fbWidth, fbHeight);

	static unsigned int shaderProgram{};

	if(shaderProgram == 0)
	{
		// Use program
		constexpr auto* vertexShader =
			"#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\0";

		unsigned int vtxSdr = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vtxSdr, 1, &vertexShader, nullptr);
		glCompileShader(vtxSdr);

		constexpr auto* fragmentShaderSource = R"(
			#version 330 core
			out vec4 FragColor;

			void main()
			{
				FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
			} 
		)";

		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
		glCompileShader(fragmentShader);

		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vtxSdr);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glDeleteShader(vtxSdr);
		glDeleteShader(fragmentShader);
	}

	// Vertex Buffer
	std::array vertices{-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

	static unsigned int vao{};

	if(vao == 0)
	{
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
	}

	static unsigned int vbo{};

	if(vbo == 0)
	{
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		// OnDirty
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	}

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glUseProgram(shaderProgram);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glfwSwapBuffers(this->pimpl->window);
	glfwPollEvents();
}
