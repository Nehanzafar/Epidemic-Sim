// our own code
#include "Window.h"

Window::Window()
{
    this->sim = new Simulation(20, 100, {0, 0, 0, 0}, screen_width, screen_height, 10);
    InitWindow(screen_width, screen_height, "Epidemeology Sim");
    SetTargetFPS(30);
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
        // sim->draw_grid();
        EndDrawing();

        if(sim->population_count() == 0) return;

    }

    CloseWindow();
    std::cout << "HEllo WOlrd";
}
