//
// Created by Tristan on 8/26/2024.
//
#define RAYGUI_IMPLEMENTATION

#include "raylib.h"
#include "layouts/index.hpp"

int main() {
// Initialization
    //---------------------------------------------------------------------------------------
    int screenWidth = 1080;
    int screenHeight = 740;

    InitWindow(screenWidth, screenHeight, "Cheese");

   cheese::IndexLayout iLayout{screenWidth, screenHeight};

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        iLayout.update();
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        iLayout.draw();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}