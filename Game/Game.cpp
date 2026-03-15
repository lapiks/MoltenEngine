#include "Game.h"

bool Game::Initialize(const Window& window) {
	if (!m_renderDevice.Initialize(window)) {
		return false;
	}

	return true;
}

void Game::Shutdown() {
}

void Game::Update() {
	const float dt = m_time.GetDeltaTime();
	dt;
}

void Game::Render() {
}
