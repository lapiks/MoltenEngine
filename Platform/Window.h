class GLFWwindow;

class Window {
private:
	GLFWwindow* m_window;

public:
	bool Create(int width, int heigth);
	void Destroy();
	bool ShouldClose() const;
	void PollEvents() const;
};