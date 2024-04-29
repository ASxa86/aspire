#pragma once

#include <aspire/core/Pimpl.h>

namespace aspire::render
{
	class VulkanInstance
	{
	public:
		auto create() -> bool;
		auto destroy() -> void;

	private:
		struct Impl;
		Pimpl<Impl> pimpl;
	};
}