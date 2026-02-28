#include "Window.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <cstdlib>

bool Window::Create(int width, int heigth) {
    if (!glfwInit()) {
        return false;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    m_window = glfwCreateWindow(width, heigth, "Molten Engine", NULL, NULL);
    if (!m_window) {
        return false;
    }

    return true;
}

void Window::Destroy() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

bool Window::ShouldClose() const {
	return glfwWindowShouldClose(m_window);
}

void Window::PollEvents() const {
    glfwPollEvents();
}
