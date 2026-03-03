#include "Engine.h"
#include "Platform/Window.h"

void Engine::Initialize(const Window& window, const EngineConfig& config) {
	m_renderDevice.Initialize(window);
}

void Engine::Shutdown() {
}

void Engine::Update() {
	const float dt = m_time.GetDeltaTime();
	dt;
}

void Engine::Render() {
}
