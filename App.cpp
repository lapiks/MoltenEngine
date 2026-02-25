#include "app.h"

#include "Platform/Window.h"
#include <cstdlib>

int App::Run()
{
    Window window;
    if (!window.Create(640, 480)) {
        return EXIT_FAILURE;
    }

    while (!window.ShouldClose()) {
        window.PollEvents();
    }

    window.Destroy();

    return EXIT_SUCCESS;
}
