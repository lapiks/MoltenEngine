class GLFWwindow;

class Window {
public:
	bool Create(int width, int heigth);
	void Destroy();
	bool ShouldClose() const;
	void PollEvents() const;

private:
	GLFWwindow* m_window;
};