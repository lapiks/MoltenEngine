#include "RenderDevice.h"

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

bool RenderDevice::Initialize(const std::vector<const char*>& instanceExtensions) {
    std::println("Initializing Vulkan");

    VkApplicationInfo appInfo{
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = "Molten Engine",
        .apiVersion = VK_API_VERSION_1_3
    };

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