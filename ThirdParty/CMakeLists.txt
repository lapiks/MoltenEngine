add_subdirectory(glfw-3.4)
add_subdirectory(glm-1.0.3)
add_subdirectory(flecs-4.1.4)

add_library(ThirdParty INTERFACE)

target_link_libraries(ThirdParty
    INTERFACE
        glfw
        glm
        flecs::flecs_static
)