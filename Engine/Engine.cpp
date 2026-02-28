#include "Engine.h"

void Engine::Initialize(const EngineConfig& config) {
	m_renderDevice.Initialize(config.instanceExtensions);
}

void Engine::Shutdown() {
}

void Engine::Update() {
	const float dt = m_time.GetDeltaTime();
	dt;
}

void Engine::Render() {
}
