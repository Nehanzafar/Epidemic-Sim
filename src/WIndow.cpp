#include <raylib.h>
#include "Window.h"

Window::Window()
{

    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);
}

void Window::Run()
{
    const Color darkGreen = {20, 160, 133, 255};
    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(darkGreen);

        EndDrawing();
    }

    CloseWindow();
}