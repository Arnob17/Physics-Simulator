#include "../include/logic.h"
#include <memory>
#include <string>
// g++ src/main.cpp src/logic.cpp src/objects.cpp -Iinclude -o build/game.exe -lraylib -lopengl32 -lgdi32 -lwinmm
int main()
{
    // Initialize window
    InitWindow(800, 600, "Physics Engine: PhiOcean");
    SetTargetFPS(2);

    // std::string msg = "Physics Engine: PhiOcean 1.0\n"
    //                   "Graphics Engine: Raylib 4.0\n"
    //                   "C++ Standard: C++17";

    // Create physics simulator
    PhysicsSimulator simulator({0.0f, 981.0f}); // Gravity scaled up for visibility

    // Add circles to simulate
    simulator.addObject(std::make_unique<Circle>(
        Vector2{200, 100}, // position
        Vector2{200, 0},   // initial velocity
        1.0f,              // mass
        20.0f,             // radius
        RED                // color
        ));

    simulator.addObject(std::make_unique<Circle>(
        Vector2{600, 100}, // position
        Vector2{-200, 0},  // initial velocity
        1.0f,              // mass
	20.0f,             // radius
        BLUE               // color
        ));

    // Add rectangles to simulate
    simulator.addObject(std::make_unique<PhysicsRectangle>(
        Vector2{400, 200}, // position
        Vector2{0, 0},     // initial velocity
        2.0f,              // mass
        80.0f,             // width
        40.0f,             // height
        GREEN              // color
        ));

    simulator.addObject(std::make_unique<PhysicsRectangle>(
        Vector2{300, 400},  // position
        Vector2{100, -150}, // initial velocity
        1.5f,               // mass
        60.0f,              // width
        60.0f,              // height
        PURPLE              // color
        ));

    // Add floor (centered near bottom). Use mass <= 0 to mark immovable/static.
    simulator.addObject(std::make_unique<floorPhysicsRectangle>(
        Vector2{400, 590},   // position (centered x=400, near bottom y=590)
        Vector2{0, 0},       // initial velocity
        0.0f,                // mass (immovable)
        800.0f,              // width
        20.0f,               // height
        PURPLE               // color
        ));

    // Main game loop
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_ESCAPE))
        {
            break;
        }

        simulator.update();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        simulator.draw();

        DrawText("Press ESC to exit", 10, 70, 20, DARKGRAY);
        DrawFPS(10, 100);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
