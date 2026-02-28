cmake_minimum_required(VERSION 3.0...3.25)

project(
    MoltenEngine
    VERSION 0.1.0
    LANGUAGES CXX C
)

add_executable(MoltenEngine 
    "main.cpp" "App.cpp" "Platform/Window.h" "Platform/Window.cpp" "Engine/Engine.h" "Engine/Engine.cpp"   "Physics/PhysicsSystem.h" "Render/RenderSystem.h" "Core/Time.h" "Core/Time.cpp" "Render/RenderDevice.h" "Render/RenderDevice.cpp")

set_target_properties(MoltenEngine PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    COMPILE_WARNING_AS_ERROR ON
)

add_subdirectory(ThirdParty)

target_include_directories(MoltenEngine
    PRIVATE
        ${CMAKE_SOURCE_DIR}
)

target_link_libraries(MoltenEngine PRIVATE ThirdParty)
