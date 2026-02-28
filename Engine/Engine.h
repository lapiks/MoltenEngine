#include "Core/Time.h"

class Engine {
public:
	void Initialize();
	void Shutdown();
	void Update();
	void Render();

private:
	Time m_time;
};