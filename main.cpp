#include "raylib.h"
#include <string>

int main()
{
    // Initialize window
    InitWindow(800, 600, "Physics Engine: PhiOcean");
    SetTargetFPS(60);

    std::string msg = "Physics Engine: PhiOcean 1.0\n"
                      "Graphics Engine: Raylib 4.0\n"
                      "C++ Standard: C++17";

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText(msg.c_str(), 200, 280, 30, DARKBLUE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
