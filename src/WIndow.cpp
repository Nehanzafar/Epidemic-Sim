// our own code
#include "Window.h"

Window::Window()
{
    Simulation *sim = new Simulation(20, 5, {0, 0, 0, 0});
    InitWindow(screen_width, screen_height, "Epidemeology Sim");
    SetTargetFPS(60);
}

void Window::Run()
{
    sim->run_simulation();
    const Color darkGreen = {20, 160, 133, 255};
    while (!WindowShouldClose())
    {
        // sim->run_step();
        BeginDrawing();
        ClearBackground(darkGreen);
        sim->draw();
        EndDrawing();
    }

    CloseWindow();
}
