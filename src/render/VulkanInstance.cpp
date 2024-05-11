#include "VulkanInstance.h"
#include <vulkan/vulkan.h>

#include <GLFW/glfw3.h>
#include <aspire/core/PimplImpl.h>
#include <algorithm>
#include <array>
#include <optional>
#include <set>
#include <string>
#include <vector>

using aspire::render::VulkanInstance;

struct VulkanInstance::Impl
{
	auto createInstance() -> bool
	{
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "Aspire";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;
		createInfo.enabledLayerCount = 0;

		auto extensions = this->getRequiredExtensions();
		createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();

		return vkCreateInstance(&createInfo, nullptr, &this->instance) == VkResult::VK_SUCCESS;
	}

	auto createSurface(GLFWwindow* x) -> bool
	{
		return glfwCreateWindowSurface(instance, x, nullptr, &this->surface) == VK_SUCCESS;
	}

	auto pickPhysicalDevice() -> bool
	{
		uint32_t deviceCount{};
		vkEnumeratePhysicalDevices(this->instance, &deviceCount, nullptr);

		if(deviceCount == 0)
		{
			return false;
		}

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(this->instance, &deviceCount, devices.data());

		for(const auto& d : devices)
		{
			if(this->isDeviceSuitable(d))
			{
				this->physicalDevice = d;
				break;
			}
		}

		return this->physicalDevice != VK_NULL_HANDLE;
	}

	struct QueueFamilyIndices
	{
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		auto isComplete() const -> bool
		{
			return this->graphicsFamily.has_value() && this->presentFamily.has_value();
		}
	};

	auto isDeviceSuitable(VkPhysicalDevice d) -> bool
	{
		auto indices = this->findQueueFamilies(d);

		auto extensionsSupported = this->checkDeviceExtensionSupport(d);

		bool swapChainAdequate = false;
		if(extensionsSupported)
		{
			auto swapChainSupport = this->querySwapChainSupport(d);
			swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
		}

		return indices.isComplete() && extensionsSupported && swapChainAdequate;
	}

	auto checkDeviceExtensionSupport(VkPhysicalDevice d) -> bool
	{
		uint32_t extensionCount{};
		vkEnumerateDeviceExtensionProperties(d, nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(d, nullptr, &extensionCount, availableExtensions.data());

		std::set<std::string> requiredExtensions(std::begin(this->deviceExtensions), std::end(this->deviceExtensions));

		for(const auto& extension : availableExtensions)
		{
			requiredExtensions.erase(extension.extensionName);
		}

		return requiredExtensions.empty();
	}

	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice d)
	{
		QueueFamilyIndices indices{};

		uint32_t queueFamilyCount{};
		vkGetPhysicalDeviceQueueFamilyProperties(d, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(d, &queueFamilyCount, queueFamilies.data());

		auto i = 0;

		for(const auto& queueFamily : queueFamilies)
		{
			if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				indices.graphicsFamily = i;
			}

			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(d, i, this->surface, &presentSupport);

			if(presentSupport)
			{
				indices.presentFamily = i;
			}

			if(indices.isComplete())
			{
				break;
			}

			i++;
		}

		return indices;
	}

	auto getRequiredExtensions() -> std::vector<const char*>
	{
		uint32_t glfwExtensionCount{};
		const char** glfwExtensions{};
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		return std::vector<const char*>{glfwExtensions, glfwExtensions + glfwExtensionCount};
	}

	auto createLogicalDevice() -> bool
	{
		QueueFamilyIndices indices = this->findQueueFamilies(this->physicalDevice);

		VkDeviceQueueCreateInfo queueCreateInfo{};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
		queueCreateInfo.queueCount = 1;

		const auto queuePriority = 1.0f;
		queueCreateInfo.pQueuePriorities = &queuePriority;

		VkPhysicalDeviceFeatures deviceFeatures{};

		VkDeviceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pQueueCreateInfos = &queueCreateInfo;
		createInfo.queueCreateInfoCount = 1;
		createInfo.pEnabledFeatures = &deviceFeatures;
		createInfo.enabledExtensionCount = static_cast<uint32_t>(this->deviceExtensions.size());
		createInfo.ppEnabledExtensionNames = this->deviceExtensions.data();
		createInfo.enabledLayerCount = 0;

		if(vkCreateDevice(this->physicalDevice, &createInfo, nullptr, &this->device) != VK_SUCCESS)
		{
			return false;
		}

		vkGetDeviceQueue(this->device, indices.graphicsFamily.value(), 0, &this->graphicsQueue);
		vkGetDeviceQueue(this->device, indices.presentFamily.value(), 0, &this->presentQueue);

		return true;
	}

	struct SwapChainSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	auto createSwapChain(GLFWwindow* x) -> bool
	{
		auto swapChainSupport = this->querySwapChainSupport(this->physicalDevice);

		auto surfaceFormat = this->chooseSwapSurfaceFormat(swapChainSupport.formats);
		auto presentMode = this->chooseSwapPresentMode(swapChainSupport.presentModes);
		auto extent = this->chooseSwapExtent(swapChainSupport.capabilities, x);

		auto imageCount = swapChainSupport.capabilities.minImageCount + 1;
		if(swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
		{
			imageCount = swapChainSupport.capabilities.maxImageCount;
		}

		VkSwapchainCreateInfoKHR createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = surface;

		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = extent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		auto indices = this->findQueueFamilies(this->physicalDevice);
		std::array queueFamilyIndices = {indices.graphicsFamily.value(), indices.presentFamily.value()};

		if(indices.graphicsFamily != indices.presentFamily)
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices.data();
		}
		else
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		}

		createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE;

		createInfo.oldSwapchain = VK_NULL_HANDLE;

		if(vkCreateSwapchainKHR(this->device, &createInfo, nullptr, &this->swapChain) != VK_SUCCESS)
		{
			return false;
		}

		vkGetSwapchainImagesKHR(this->device, this->swapChain, &imageCount, nullptr);
		this->swapChainImages.resize(imageCount);
		vkGetSwapchainImagesKHR(this->device, this->swapChain, &imageCount, this->swapChainImages.data());

		this->swapChainImageFormat = surfaceFormat.format;
		this->swapChainExtent = extent;
		return true;
	}

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
	{
		for(const auto& availableFormat : availableFormats)
		{
			if(availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
			{
				return availableFormat;
			}
		}

		return availableFormats[0];
	}

	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
	{
		for(const auto& availablePresentMode : availablePresentModes)
		{
			if(availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
			{
				return availablePresentMode;
			}
		}

		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow* x)
	{
		if(capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
		{
			return capabilities.currentExtent;
		}
		else
		{
			auto width = 0;
			auto height = 0;
			glfwGetFramebufferSize(x, &width, &height);

			VkExtent2D actualExtent = {static_cast<uint32_t>(width), static_cast<uint32_t>(height)};

			actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
			actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

			return actualExtent;
		}
	}

	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice d)
	{
		SwapChainSupportDetails details{};

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(d, this->surface, &details.capabilities);

		uint32_t formatCount{};
		vkGetPhysicalDeviceSurfaceFormatsKHR(d, this->surface, &formatCount, nullptr);

		if(formatCount != 0)
		{
			details.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(d, this->surface, &formatCount, details.formats.data());
		}

		uint32_t presentModeCount{};
		vkGetPhysicalDeviceSurfacePresentModesKHR(d, this->surface, &presentModeCount, nullptr);

		if(presentModeCount != 0)
		{
			details.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(d, this->surface, &presentModeCount, details.presentModes.data());
		}

		return details;
	}

	const std::vector<const char*> deviceExtensions{VK_KHR_SWAPCHAIN_EXTENSION_NAME};

	VkInstance instance{};
	VkSurfaceKHR surface{};
	VkPhysicalDevice physicalDevice{VK_NULL_HANDLE};
	VkDevice device{};
	VkQueue graphicsQueue{};
	VkQueue presentQueue{};
	VkSwapchainKHR swapChain{};
	std::vector<VkImage> swapChainImages{};
	VkFormat swapChainImageFormat{};
	VkExtent2D swapChainExtent{};

	bool valid{false};
};

VulkanInstance::VulkanInstance() = default;
VulkanInstance::~VulkanInstance() = default;

auto VulkanInstance::create(GLFWwindow* x) -> bool
{
	this->pimpl->valid = true;

	this->pimpl->valid &= this->pimpl->createInstance();
	this->pimpl->valid &= this->pimpl->createSurface(x);
	this->pimpl->valid &= this->pimpl->pickPhysicalDevice();
	this->pimpl->valid &= this->pimpl->createLogicalDevice();
	this->pimpl->valid &= this->pimpl->createSwapChain(x);

	return this->pimpl->valid;
}

auto VulkanInstance::destroy() -> void
{
	vkDestroySwapchainKHR(this->pimpl->device, this->pimpl->swapChain, nullptr);
	vkDestroyDevice(this->pimpl->device, nullptr);
	vkDestroySurfaceKHR(this->pimpl->instance, this->pimpl->surface, nullptr);
	vkDestroyInstance(this->pimpl->instance, nullptr);
}

auto VulkanInstance::valid() const noexcept -> bool
{
	return this->pimpl->valid;
}