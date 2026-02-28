#include <vector>

class GLFWwindow;

class Window {
public:
	bool Create(int width, int heigth);
	void Destroy();
	bool ShouldClose() const;
	void PollEvents() const;
	std::vector<const char*> GetRequiredInstanceExtensions() const;

private:
	GLFWwindow* m_window;
};