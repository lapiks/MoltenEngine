add_subdirectory(glfw-3.4)
add_subdirectory(glm-1.0.3)
add_subdirectory(flecs-4.1.4)
add_subdirectory(imgui-1.92.6)
add_subdirectory(VulkanMemoryAllocator-3.3.0)

add_library(ThirdParty INTERFACE)

find_package(Vulkan REQUIRED)

target_link_libraries(ThirdParty
    INTERFACE
        glfw
        glm
        flecs::flecs_static
        imgui
        Vulkan::Vulkan
        GPUOpen::VulkanMemoryAllocator
)