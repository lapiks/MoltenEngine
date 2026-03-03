#include "RenderDevice.h"

#include "Platform/Window.h"

#include <print>
#include <iostream>
#include <vulkan/vulkan.h>
#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>

inline bool VK_CHECK_BOOL(VkResult result, const char* msg) {
    if (result != VK_SUCCESS) {
        std::cerr << "Vulkan error: " << msg << " (VkResult=" << result << ")\n";
        return false;
    }
    return true;
}

#define VK_CHECK_RETURN(x) \
    do { if (!VK_CHECK_BOOL((x), #x)) return false; } while(0)

bool RenderDevice::Initialize(const Window& window) {
    std::println("Initializing Vulkan");

    VkApplicationInfo appInfo{
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = "Molten Engine",
        .apiVersion = VK_API_VERSION_1_3
    };

    auto instanceExtensions = window.GetRequiredInstanceExtensions();

    VkInstanceCreateInfo instanceCI{
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &appInfo,
        .enabledExtensionCount = (uint32_t)instanceExtensions.size(),
        .ppEnabledExtensionNames = instanceExtensions.data(),
        };

    VkInstance instance;
    VK_CHECK_RETURN(vkCreateInstance(&instanceCI, nullptr, &instance));

    uint32_t deviceCount{ 0 };
    VK_CHECK_RETURN(vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr));

    if (deviceCount < 1) {
        std::println("No physical device");
        return false;
    }

    uint32_t deviceIndex{ 0 };
    std::vector<VkPhysicalDevice> devices(deviceCount);
    VK_CHECK_RETURN(vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data()));
    VkPhysicalDeviceProperties2 deviceProperties{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2 };
    vkGetPhysicalDeviceProperties2(devices[deviceIndex], &deviceProperties);

    std::println("Selected device: {}", deviceProperties.properties.deviceName);

    uint32_t queueFamilyCount{ 0 };
    vkGetPhysicalDeviceQueueFamilyProperties(devices[deviceIndex], &queueFamilyCount, nullptr);
    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(devices[deviceIndex], &queueFamilyCount, queueFamilies.data());
    uint32_t queueFamily{ 0 };
    for (size_t i = 0; i < queueFamilies.size(); i++) {
        if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            queueFamily = i;
            break;
        }
    }

    const float qfpriorities{ 1.0f };
    VkDeviceQueueCreateInfo queueCI{
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .queueFamilyIndex = queueFamily,
        .queueCount = 1,
        .pQueuePriorities = &qfpriorities
    };

    const std::vector<const char*> deviceExtensions{ VK_KHR_SWAPCHAIN_EXTENSION_NAME };

    VkPhysicalDeviceVulkan12Features enabledVk12Features{
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES,
        .descriptorIndexing = true,
        .shaderSampledImageArrayNonUniformIndexing = true,
        .descriptorBindingVariableDescriptorCount = true,
        .runtimeDescriptorArray = true,
        .bufferDeviceAddress = true
    };
    const VkPhysicalDeviceVulkan13Features enabledVk13Features{
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES,
        .pNext = &enabledVk12Features,
        .synchronization2 = true,
        .dynamicRendering = true,
    };
    const VkPhysicalDeviceFeatures enabledVk10Features{
        .samplerAnisotropy = VK_TRUE
    };

    VkDeviceCreateInfo deviceCI{
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .pNext = &enabledVk13Features,
        .queueCreateInfoCount = 1,
        .pQueueCreateInfos = &queueCI,
        .enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size()),
        .ppEnabledExtensionNames = deviceExtensions.data(),
        .pEnabledFeatures = &enabledVk10Features
    };
    VkDevice device;
    VK_CHECK_RETURN(vkCreateDevice(devices[deviceIndex], &deviceCI, nullptr, &device));

    VkQueue queue;
    vkGetDeviceQueue(device, queueFamily, 0, &queue);

    VmaVulkanFunctions vkFunctions{
        .vkGetInstanceProcAddr = vkGetInstanceProcAddr,
        .vkGetDeviceProcAddr = vkGetDeviceProcAddr,
        .vkCreateImage = vkCreateImage
    };
    VmaAllocatorCreateInfo allocatorCI{
        .flags = VMA_ALLOCATOR_CREATE_BUFFER_DEVICE_ADDRESS_BIT,
        .physicalDevice = devices[deviceIndex],
        .device = device,
        .pVulkanFunctions = &vkFunctions,
        .instance = instance
    };
    VmaAllocator allocator;
    VK_CHECK_RETURN(vmaCreateAllocator(&allocatorCI, &allocator));

    VkSurfaceKHR surface;
    VK_CHECK_RETURN(window.CreateSurface(instance, surface));

    VkSurfaceCapabilitiesKHR surfaceCaps{};
    VK_CHECK_RETURN(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(devices[deviceIndex], surface, &surfaceCaps));

    const VkFormat imageFormat{ VK_FORMAT_B8G8R8A8_SRGB };
    VkSwapchainCreateInfoKHR swapchainCI{
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .surface = surface,
        .minImageCount = surfaceCaps.minImageCount,
        .imageFormat = imageFormat,
        .imageColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR,
        .imageExtent{.width = surfaceCaps.currentExtent.width, .height = surfaceCaps.currentExtent.height },
        .imageArrayLayers = 1,
        .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
        .preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
        .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        .presentMode = VK_PRESENT_MODE_FIFO_KHR
    };

    VkSwapchainKHR swapchain;
    VK_CHECK_RETURN(vkCreateSwapchainKHR(device, &swapchainCI, nullptr, &swapchain));

    uint32_t imageCount{ 0 };
    VK_CHECK_RETURN(vkGetSwapchainImagesKHR(device, swapchain, &imageCount, nullptr));
    std::vector<VkImage> swapchainImages;
    swapchainImages.resize(imageCount);

    VK_CHECK_RETURN(vkGetSwapchainImagesKHR(device, swapchain, &imageCount, swapchainImages.data()));
    std::vector<VkImageView> swapchainImageViews;
    swapchainImageViews.resize(imageCount);

    std::vector<VkFormat> depthFormatList{ VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT };
    VkFormat depthFormat{ VK_FORMAT_UNDEFINED };
    for (VkFormat& format : depthFormatList) {
        VkFormatProperties2 formatProperties{ .sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2 };
        vkGetPhysicalDeviceFormatProperties2(devices[deviceIndex], format, &formatProperties);
        if (formatProperties.formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
            depthFormat = format;
            break;
        }
    }

    VkImageCreateInfo depthImageCI{
        .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        .imageType = VK_IMAGE_TYPE_2D,
        .format = depthFormat,
        .extent{.width = window.GetWidth(), .height = window.GetHeight(), .depth = 1},
        .mipLevels = 1,
        .arrayLayers = 1,
        .samples = VK_SAMPLE_COUNT_1_BIT,
        .tiling = VK_IMAGE_TILING_OPTIMAL,
        .usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
    };

    VmaAllocationCreateInfo allocCI{
        .flags = VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT,
        .usage = VMA_MEMORY_USAGE_AUTO
    };
    VmaAllocation depthImageAllocation;
    VkImage depthImage;
    VK_CHECK_RETURN(vmaCreateImage(allocator, &depthImageCI, &allocCI, &depthImage, &depthImageAllocation, nullptr));

    VkImageViewCreateInfo depthViewCI{
        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        .image = depthImage,
        .viewType = VK_IMAGE_VIEW_TYPE_2D,
        .format = depthFormat,
        .subresourceRange{.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT, .levelCount = 1, .layerCount = 1 }
    };
    VkImageView depthImageView;
    VK_CHECK_RETURN(vkCreateImageView(device, &depthViewCI, nullptr, &depthImageView));

    return true;
}

void RenderDevice::Shutdown() {
}

void RenderDevice::CreateTexture() {
}

void RenderDevice::CreateBuffer() {
}

void RenderDevice::CreateRenderPipeline() {
}

void RenderDevice::CreateShader() {
}

void RenderDevice::DestroyTexture() {
}

void RenderDevice::DestroyBuffer() {
}

void RenderDevice::DestroyRenderPipeline() {
}

void RenderDevice::DestroyShader() {
}

void RenderDevice::SetRenderPipeline() {
}

void RenderDevice::Draw() {
}