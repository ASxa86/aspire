#pragma once

#include <aspire/Program.h>
#include <stack>

namespace aspire
{
	/// @brief This class manages the pushing/popping of current OpenGL state.
	class State
	{
	public:
		State();

		/// @brief Push the given progam to the stack making it the current program.
		/// @param x The program to be added to the state.
		auto pushProgram(aspire::Program* x) -> void;

		/// @brief Pop the current program off of the stack.
		auto popProgram() -> void;

		/// @brief Get the current program on the stack.
		/// @return A pointer to the current program.
		auto currentProgram() const -> aspire::Program*;

	private:
		aspire::Program programDefault;
		std::stack<aspire::Program*> programs;
	};
}
