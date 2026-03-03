#include "Core/Time.h"
#include "Render/RenderDevice.h"

struct EngineConfig {
	
};

class Engine {
public:
	void Initialize(const Window& window, const EngineConfig& config);
	void Shutdown();
	void Update();
	void Render();

private:
	Time m_time;
	RenderDevice m_renderDevice;
};