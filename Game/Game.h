#include "Core/Time.h"
#include "Render/RenderDevice.h"

class Game {
public:
	bool Initialize(const Window& window);
	void Shutdown();

	void Update();
	void Render();

private:
	Time m_time;
	RenderDevice m_renderDevice;
};