#include <vector>
#include <vulkan/vulkan.h>

class GLFWwindow;

class Window {
public:
	bool Create(int width, int heigth);
	void Destroy();
	int GetWidth() const;
	int GetHeight() const;
	bool ShouldClose() const;
	void PollEvents() const;
	std::vector<const char*> GetRequiredInstanceExtensions() const;
	VkResult CreateSurface(VkInstance instance, VkSurfaceKHR& surface) const;

private:
	GLFWwindow* m_window;
	int m_width;
	int m_height;
};