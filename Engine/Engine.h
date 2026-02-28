#include "Core/Time.h"
#include "Render/RenderDevice.h"

struct EngineConfig {
	std::vector<const char*> instanceExtensions;
};

class Engine {
public:
	void Initialize(const EngineConfig& config);
	void Shutdown();
	void Update();
	void Render();

private:
	Time m_time;
	RenderDevice m_renderDevice;
};