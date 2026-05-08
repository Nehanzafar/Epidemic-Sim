// our own code
#include "Window.h"
using namespace std;

Window::Window()
{
    bool choice;
    cout << "----------Welcome To The Epidemeology Sim----------" << endl;
    cout << "Do you want to run on the suggested parameters (1 yes/0 no) :";
    cin >> choice;
    switch (choice)
    {
    case 1:
        this->sim = new Simulation(100, {0, 0, 0, 0}, screen_width, screen_height, 10);
        break;
    case 0:
        // int population;
        // float fatality,infectivity,recovery_time;
        // cout <<"Enter The Fatality Of Disease (0-0.5): "
        // break;
    default:
        break;
    }

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
        if (sim->population_count() == 0)
            return;
    }
    CloseWindow();
    std::cout << "Hello World";
}
