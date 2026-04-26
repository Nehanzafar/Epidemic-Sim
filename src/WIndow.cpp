#include <raylib.h>
#include "Window.h"
#include "Agent.h"
#include <vector>

Window::Window()
{

    const int screen_width = 800;
    const int screen_height = 600;
    InitWindow(screen_width, screen_height, "Epidemeology Sim");
    SetTargetFPS(60);
}


void Window::Run(std::vector<Agent> a)
{
    const Color darkGreen = {20, 160, 133, 255};
    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(darkGreen);
        for (int i = 0; i < a.size(); i++)
        {
            a[i].Draw();
        }
        EndDrawing();
    }

    CloseWindow();
}