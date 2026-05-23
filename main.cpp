#include "raylib.h"
#include "integrator.h"
#include "atom.h"
#include "forcefield.h"
#include <vector>
#include <iostream>

int main() {
    std::vector<Atom> atoms;

    for(int i = 0 ; i < 5; i++){
        Atom a ;
        a.type = "C";
        a.position = Vec3(i * 3.3 , 0 , 0 );
        a.velocity = Vec3( 0 , 0 , 0);
        a.mass = 12.0;
        a.epsilon = 0.1094;
        a.sigma = 3.40;
        a.charge = 0.55;
        atoms.push_back(a);
    }

    for(int i = 0 ; i < 5 ; i++){
        Atom a; 
        a.type = "O";
        a.position = Vec3(i * 3.3, 5.0, 0.0);
        a.velocity = Vec3(0.0, 0.0, 0.0);
        a.mass = 16.0;
        a.epsilon = 0.2092;
        a.sigma = 2.96;
        a.charge = -0.55;
        atoms.push_back(a);
    }

    
    srand(time(nullptr));
    for(auto& atom : atoms) {
        atom.velocity.x = (rand() / (double)RAND_MAX - 0.5) * 0.01;
        atom.velocity.y = (rand() / (double)RAND_MAX - 0.5) * 0.01;
        atom.velocity.z = (rand() / (double)RAND_MAX - 0.5) * 0.01;
    }

    std::cout << "Created " << atoms.size() << " atoms\n";
    for(int i = 0; i < atoms.size(); i++){
        std::cout << "Atom " << i << " (" << atoms[i].type << "): x=" << atoms[i].position.x 
                  << " y=" << atoms[i].position.y << " charge=" << atoms[i].charge << "\n";
    }

   

    const int screenwidth = 1000;
    const int screenheight = 700;
    InitWindow(screenwidth,screenheight, "Molsim Engine  v0.3 - 10 Atoms");

    Camera3D camera = {0};
    camera.position = Vector3{3.0f, 1.0f, 15.0f};
    camera.target = Vector3{6.0f, 2.5f, 0.0f};
    camera.up = Vector3{0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);
    double dt = 0.001;

    while(!WindowShouldClose()){
        for(int step = 0 ; step <100 ; step++){
            velocity_verlet_step(atoms , dt);
        }

        UpdateCamera(&camera , CAMERA_ORBITAL);
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode3D(camera);

        DrawGrid(20 , 1.0f);

        for(const auto& atom: atoms){
            Color atomColor;
            float radius;
            if(atom.type == "C"){
                atomColor = DARKGRAY;
                radius = 0.5f;
            }else{
                atomColor = RED;
                radius = 0.4f;
            }
            DrawSphere(Vector3{(float)atom.position.x , (float)atom.position.y , (float)atom.position.z } , radius , atomColor);
        }
        EndMode3D();

        DrawText("MolSim Engine v0.3 - 10 Atoms", 10, 10, 24, WHITE);
        DrawText("5 Carbon (gray) + 5 Oxygen (red)", 10, 40, 18, LIGHTGRAY);
        DrawText("Drag mouse to orbit | Scroll to zoom", 10, screenheight - 30, 16, GRAY);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}