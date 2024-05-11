#pragma once

#include <aspire/core/Pimpl.h>

class GLFWwindow;

namespace aspire::render
{
	class VulkanInstance
	{
	public:
		VulkanInstance();
		~VulkanInstance();

		auto create(GLFWwindow* x) -> bool;
		auto destroy() -> void;
		auto valid() const noexcept -> bool;

	private:
		struct Impl;
		Pimpl<Impl> pimpl;
	};
}