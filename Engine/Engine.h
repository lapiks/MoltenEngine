#include "Core/Time.h"

class Engine {
private:
	Time m_time;

public:
	void Initialize();
	void Shutdown();
	void Update();
	void Render();
};