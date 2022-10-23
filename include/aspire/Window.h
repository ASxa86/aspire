#pragma once

#include <aspire/Event.h>
#include <aspire/export.hxx>
#include <string>
#include <vector>

class GLFWwindow;

namespace aspire
{
	class ASPIRE_EXPORT Window
	{
	public:
		struct Traits
		{
			static constexpr auto DefaultWidth{1280};
			static constexpr auto DefaultHeight{720};

			std::string title{};
			int width{DefaultWidth};
			int height{DefaultHeight};
			bool windowDecoration{true};
		};

		Window(Traits x = {});
		~Window();

		auto open() const -> bool;
		auto run() -> int;

		auto frame(std::chrono::steady_clock::duration x) -> void;
		auto frameEvent() -> void;

	private:
		Traits traits{};
		std::vector<Event> events;
		std::chrono::steady_clock::duration elapsed{};
		GLFWwindow* window{nullptr};
		bool glfwInitialized{false};
		bool gladInitialized{false};
		bool done{false};
	};
}
