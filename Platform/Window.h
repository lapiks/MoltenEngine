#include <vector>
#include <vulkan/vulkan.h>

class GLFWwindow;

class Window {
public:
	bool Create(uint32_t width, uint32_t heigth);
	void Destroy();
	uint32_t GetWidth() const;
	uint32_t GetHeight() const;
	bool ShouldClose() const;
	void PollEvents() const;
	std::vector<const char*> GetRequiredInstanceExtensions() const;
	VkResult CreateSurface(VkInstance instance, VkSurfaceKHR& surface) const;

private:
	GLFWwindow* m_window;
	uint32_t m_width;
	uint32_t m_height;
};