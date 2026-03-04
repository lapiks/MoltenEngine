#include "Window.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <cstdlib>

bool Window::Create(uint32_t width, uint32_t heigth) {
    if (!glfwInit()) {
        return false;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    m_window = glfwCreateWindow(width, heigth, "Molten Engine", NULL, NULL);
    if (!m_window) {
        return false;
    }

    m_width = width;
    m_height = heigth;

    return true;
}

void Window::Destroy() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

uint32_t Window::GetWidth() const {
    return m_width;
}

uint32_t Window::GetHeight() const {
    return m_height;
}

bool Window::ShouldClose() const {
	return glfwWindowShouldClose(m_window);
}

void Window::PollEvents() const {
    glfwPollEvents();
}

std::vector<const char*> Window::GetRequiredInstanceExtensions() const {
    uint32_t count = 0;
    const char** extensions = glfwGetRequiredInstanceExtensions(&count);

    return std::vector<const char*>(extensions, extensions + count);
}

VkResult Window::CreateSurface(VkInstance instance, VkSurfaceKHR& surface) const {
    return glfwCreateWindowSurface(instance, m_window, NULL, &surface);
}
