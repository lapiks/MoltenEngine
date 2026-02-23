#include "App.h"

#include <GLFW/glfw3.h>
#include <cstdlib>

int App::run()
{
    if (!glfwInit()) {
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    GLFWwindow* window = glfwCreateWindow(640, 480, "Molten Engine", NULL, NULL);
    if (!window) {
        return EXIT_FAILURE;
    }

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}
