#include "raylib.h"
#include "atom.h"
#include "forcefield.h"
#include <iostream>

int main() {
    Atom carbon;
    carbon.type = "C";
    carbon.position = Vec3(0.0, 0.0, 0.0);
    carbon.epsilon = 0.1094;
    carbon.sigma = 3.40;
    carbon.charge = 0.0;

    Atom oxygen;
    oxygen.type = "O";
    oxygen.position = Vec3(4.0, 0.0, 0.0);
    oxygen.epsilon = 0.2092;
    oxygen.sigma = 2.96;
    oxygen.charge = -0.55;

    double energy = total_pair_energy(carbon, oxygen);
    std::cout << "Distance: " << (carbon.position - oxygen.position).length() << " A" << std::endl;
    std::cout << "LJ Energy: " << lennard_jones_potential(carbon, oxygen) << " kcal/mol" << std::endl;
    std::cout << "Coulomb Energy: " << coulomb_potential(carbon, oxygen) << " kcal/mol" << std::endl;
    std::cout << "Total Energy: " << energy << " kcal/mol" << std::endl;

    const int screenWidth = 1000;
    const int screenHeight = 700;
    InitWindow(screenWidth, screenHeight, "MolSim Engine v0.1");

    Camera3D camera = {0};
    camera.position = Vector3{10.0f, 6.0f, 10.0f};
    camera.target = Vector3{2.0f, 0.0f, 0.0f};
    camera.up = Vector3{0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_ORBITAL);
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode3D(camera);

        DrawGrid(20, 1.0f);
        DrawLine3D(Vector3{-10,0,0}, Vector3{10,0,0}, RED);
        DrawLine3D(Vector3{0,-10,0}, Vector3{0,10,0}, GREEN);
        DrawLine3D(Vector3{0,0,-10}, Vector3{0,0,10}, BLUE);

        DrawSphere(Vector3{0,0,0}, 0.6f, DARKGRAY);
        DrawSphere(Vector3{4,0,0}, 0.5f, RED);
        DrawLine3D(Vector3{0,0,0}, Vector3{4,0,0}, WHITE);

        EndMode3D();

        DrawText("MolSim Engine v0.1", 10, 10, 24, WHITE);
        DrawText("Carbon (C) - Dark Gray", 10, 40, 18, LIGHTGRAY);
        DrawText("Oxygen (O) - Red", 10, 60, 18, LIGHTGRAY);
        DrawText(TextFormat("Distance: %.2f A", 4.0), 10, 90, 18, YELLOW);
        DrawText(TextFormat("LJ Energy: %.4f kcal/mol", lennard_jones_potential(carbon, oxygen)), 10, 115, 18, YELLOW);
        DrawText(TextFormat("Coulomb Energy: %.4f kcal/mol", coulomb_potential(carbon, oxygen)), 10, 135, 18, YELLOW);
        DrawText(TextFormat("Total Energy: %.4f kcal/mol", energy), 10, 160, 20, GREEN);
        DrawText("Drag mouse to orbit | Scroll to zoom", 10, screenHeight - 30, 16, GRAY);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}