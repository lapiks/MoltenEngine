#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

int main (int, char**) {
    std::cout << "Hello, world!" << std::endl;

    if (!glfwInit())
    {
        return 0;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    GLFWwindow* window = glfwCreateWindow(640, 480, "Molten Engine", NULL, NULL);
    if (!window)
    {
        // Window or OpenGL context creation failed
    }

    glm::mat4 matrix;
    glm::vec4 vec;
    auto test = matrix * vec;

    while (!glfwWindowShouldClose(window)) 
    {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}