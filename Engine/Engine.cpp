#include "Engine.h"
#include "Platform/Window.h"

bool Engine::Initialize(const Window& window, const EngineConfig& config) {
	if (!m_renderDevice.Initialize(window)) {
		return false;
	}

	return true;
}

void Engine::Shutdown() {
}

void Engine::Update() {
	const float dt = m_time.GetDeltaTime();
	dt;
}

void Engine::Render() {
}
