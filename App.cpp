#include "app.h"

#include <cstdlib>

#include "Platform/Window.h"
#include "Engine/Engine.h"

int App::Run()
{
    Window window;
    if (!window.Create(640, 480)) {
        return EXIT_FAILURE;
    }

    EngineConfig config;

    Engine engine;
    engine.Initialize(window, config);

    while (!window.ShouldClose()) {
        window.PollEvents();

        engine.Update();
        engine.Render();
    }

    engine.Shutdown();
    window.Destroy();

    return EXIT_SUCCESS;
}
