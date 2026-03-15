#include "app.h"

#include <cstdlib>

#include "Platform/Window.h"
#include "Game/Game.h"

int App::Run()
{
    Window window;
    if (!window.Create(640, 480)) {
        return EXIT_FAILURE;
    }

    Game game;
    if (!game.Initialize(window)) {
        return EXIT_FAILURE;
    }

    while (!window.ShouldClose()) {
        window.PollEvents();

        game.Update();
        game.Render();
    }

    game.Shutdown();
    window.Destroy();

    return EXIT_SUCCESS;
}
