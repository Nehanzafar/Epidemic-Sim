#include <raylib.h>
#include "Window.h"
#include "Agent.h"
#include "Simulation.h"
#include <vector>

Window::Window()
{
    Simulation *sim = new Simulation(20, 20, {0, 0, 0, 0});
    InitWindow(screen_width, screen_height, "Epidemeology Sim");
    SetTargetFPS(60);
}

void Window::Run()
{
    sim->run_simulation();
    const Color darkGreen = {20, 160, 133, 255};
    while (!WindowShouldClose())
    {
        sim->run_step();
        BeginDrawing();
        ClearBackground(darkGreen);
        sim->draw();
        EndDrawing();
    }

    CloseWindow();
}
