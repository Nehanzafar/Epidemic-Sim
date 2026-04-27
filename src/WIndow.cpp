// our own code
#include "Window.h"

Window::Window()
{
    this->sim = new Simulation(20, 20, {0, 0, 0, 0});
    InitWindow(screen_width, screen_height, "Epidemeology Sim");
    SetTargetFPS(60);
}

void Window::Run()
{
    sim->run_simulation();
    while (!WindowShouldClose())
    {
        sim->run_step();
        BeginDrawing();
        ClearBackground(BLACK);
        sim->draw();
        EndDrawing();
    }

    CloseWindow();
}
