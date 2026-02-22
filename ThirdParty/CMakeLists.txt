add_subdirectory(glfw)
add_subdirectory(glm)

add_library(ThirdParty INTERFACE)

target_link_libraries(ThirdParty
    INTERFACE
        glfw
        glm
)