#include "VulkanInstance.h"
#include <vulkan/vulkan.h>

#include <aspire/core/PimplImpl.h>

using aspire::render::VulkanInstance;

struct VulkanInstance::Impl
{
	VkInstanceCreateInfo info{};
	VkAllocationCallbacks allocCallback{};
	VkInstance instance{};
};

auto VulkanInstance::create() -> bool
{
	const auto result = vkCreateInstance(&this->pimpl->info, &this->pimpl->allocCallback, &this->pimpl->instance);
	return result == VkResult::VK_SUCCESS;
}

auto VulkanInstance::destroy() -> void
{
	vkDestroyInstance(this->pimpl->instance, nullptr);
}
