#include <raylib.h>
#include "Window.h"
#include "Agent.h"
#include <vector>

Window::Window()
{

    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Epidemeology Sim");
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