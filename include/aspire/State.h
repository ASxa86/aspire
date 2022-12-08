#pragma once

#include <aspire/Program.h>
#include <stack>

namespace aspire
{
	class State
	{
	public:
		State();

		auto pushProgram(aspire::Program* x) -> void;
		auto popProgram() -> void;
		auto currentProgram() const -> aspire::Program*;

	private:
		aspire::Program programDefault;
		std::stack<aspire::Program*> programs;
	};
}
