// our own code
#include "Window.h"
using namespace std;

Window::Window()
{
    bool choice;
    cout << "----------Welcome To The Epidemeology Sim----------" << endl;
    cout << "Do you want to run on the suggested parameters (1 yes/0 no) : ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        this->sim = new Simulation(100, {0.3, 0.3, 120}, screen_width, screen_height, 10, tick);
        break;
    case 0:
        int population, recovery_time;
        float fatality, infectivity;
        do
        {
            cout << "Enter population(1-1000): ";
            cin >> population;
        } while (population <= 0 || population > 1000);
        cout << "Enter the starting disease conditions: " << endl;

        do
        {
            cout << "Enter The Fatality Of Disease (0-0.5): ";
            cin >> fatality;
        } while (fatality < 0 || fatality > 0.5);

        do
        {
            cout << "Enter The Infectivity Of Disease (0-0.5): ";
            cin >> infectivity;
        } while (infectivity < 0 || infectivity > 0.5);
        do
        {
            cout << "Enter The recovery_time Of Disease (120 - 600): ";
            cin >> recovery_time;
        } while (recovery_time < 120 || recovery_time > 600);

        this->sim = new Simulation(population, {fatality, infectivity, recovery_time}, screen_width, screen_height, 10, tick);
        ;
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
        if (sim->run_step() == 1)
            break;
        BeginDrawing();
        ClearBackground(BLACK);
        sim->draw();
        // sim->draw_grid();
        EndDrawing();
        if (sim->population_count() == 0)
            return;
    }
    CloseWindow();
    system("cd ..");
    system("python main.py");
}
