#include "Time.h"

Time::Time() : 
	m_deltaTime(0.0f),
	m_lastTime(Clock::now()),
	m_lastSec(Clock::now()),
	m_frameCount(0),
	m_fps(0)
{
}

float Time::Tick() {
	const Clock::time_point currentTime = Clock::now();
	const std::chrono::duration<float> delta = currentTime - m_lastTime;

	m_lastTime = currentTime;
	m_deltaTime = delta.count();
	m_frameCount += 1;

	if (currentTime - m_lastSec >= std::chrono::seconds(1)) {
		m_lastSec = currentTime;
		m_fps = m_frameCount;
		m_frameCount = 0;
	}

	return m_deltaTime;
}

float Time::GetFps() const {
	return m_fps;
}

float Time::GetDeltaTime() const {
	return m_deltaTime;
}

uint64_t Time::GetFrameCount() const {
	return m_frameCount;
}
