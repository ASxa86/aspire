#pragma once

#include <aspire/Event.h>
#include <aspire/Node.h>
#include <aspire/export.hxx>
#include <glm/vec4.hpp>
#include <string>
#include <vector>

class GLFWwindow;

namespace aspire
{
	class Node;

	struct Traits
	{
		static constexpr auto DefaultWidth{1280};
		static constexpr auto DefaultHeight{720};

		enum class GraphicsAPI : int
		{
			Native,
			OpenGL,
			OpenGLES,
			D3D9,
			D3D11,
			Vulkan,
			Metal
		};

		std::string title;
		int width{DefaultWidth};
		int height{DefaultHeight};
		int major{2};
		int minor{0};
		int bitsRed{8};
		int bitsGreen{8};
		int bitsBlue{8};
		int bitsAlpha{8};

		bool windowDecoration{true};
	};

	/// @brief This class represents a single window and graphics context.
	class ASPIRE_EXPORT Window
	{
	public:
		Window(aspire::Traits x = {});
		~Window();

		auto makeCurrent() -> void;
		auto makeRelease() -> void;
		auto clear() -> void;
		auto swapBuffers() -> void;

		/// @brief Return whether the window is open.
		/// @return bool True if the window is open.
		auto open() const -> bool;

		/// @brief Run the processing/rendering loop in a default configuration.
		/// @return int Exit code. 0 on success.
		auto run() -> int;

		/// @brief Process a single frame of events, updates, draws, etc...
		/// @param x The elapsed time between frames.
		/// @return void
		auto frame(std::chrono::steady_clock::duration x) -> void;

		/// @brief Process queued events and forward them to the scene.
		/// @return void
		auto frameEvent() -> void;

		/// @brief Process update logic for the scene.
		/// @return void
		auto frameUpdate() -> void;

		/// @brief Process render logic for the scene.
		/// @return void
		auto frameDraw() -> void;

		/// @brief Set the root node for the scene.
		/// @param x The root node to being the scene traversal.
		/// @return void
		auto setNode(Node& x) -> void;

		/// @brief Get the root node to the scene.
		/// @return aspire::Node* The root node of the scene.
		auto getNode() const -> Node*;

	private:
		aspire::Traits traits{};
		std::vector<Event> events;
		glm::vec4 clearColor{0.0F, 0.0F, 0.0F, 1.0F};
		std::chrono::steady_clock::duration elapsed{};
		GLFWwindow* window{nullptr};
		Node* root{nullptr};
		bool glfwInitialized{false};
		bool gladInitialized{false};
		bool done{false};
	};
}
