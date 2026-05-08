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
        this->sim = new Simulation(100, {0.3, 0.3, 150}, screen_width, screen_height, 10, tick);
        break;
    case 0:
        int population, recovery_time;
        float fatality, infectivity;
        cout << "Enter the starting disease conditions: " << endl;
        cout << "Enter The Fatality Of Disease (0-0.5): ";
        cin >> fatality;
        cout << "Enter The Infectivity Of Disease (0-0.5): ";
        cin >> infectivity;
        cout << "Enter The recovery_time Of Disease (120 - 600): ";
        cin >> recovery_time;

        this->sim = new Simulation(population, {fatality, infectivity, recovery_time}, screen_width, screen_height, 10, tick);
        break;
    default:
        break;
    }

    InitWindow(screen_width, screen_height, "Epidemeology Sim");
    SetTargetFPS(tick);
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

}
