#include <chrono>

class Time {
private:
	using Clock = std::chrono::steady_clock;

	float m_deltaTime;
	Clock::time_point m_lastTime;
	Clock::time_point m_lastSec;
	uint64_t m_frameCount;
	uint64_t m_fps;

public:
	Time();
	float Tick();
	float GetFps() const;
	float GetDeltaTime() const;
	uint64_t GetFrameCount() const;
};