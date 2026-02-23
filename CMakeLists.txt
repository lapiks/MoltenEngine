cmake_minimum_required(VERSION 3.0...3.25)

project(
    MoltenEngine
    VERSION 0.1.0
    LANGUAGES CXX C
)

add_executable(MoltenEngine 
    main.cpp
 "App.cpp")

set_target_properties(MoltenEngine PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    COMPILE_WARNING_AS_ERROR ON
)

add_subdirectory(ThirdParty)

target_link_libraries(MoltenEngine PRIVATE ThirdParty)