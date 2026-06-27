#include "raylib.h"
int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "Raylib Test");
    SetWindowPosition(200, 200);
    SetTargetFPS(60);
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(Color{20, 20, 40, 255});
        DrawText("If you can read this, Raylib works!", 100, 250, 24, WHITE);
        DrawFPS(10, 10);
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
