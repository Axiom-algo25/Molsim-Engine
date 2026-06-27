#include "raylib.h"
#include "integrator.h"
#include "atom.h"
#include "forcefield.h"
#include <vector>
#include <iostream>
#include "pdb_parser.h"

int main() {
    std::vector<Atom> atoms;

    std::cout << "PDB PARSER VERSION 999\n";
    atoms = load_pdb("1CRN.pdb");
    std::vector<Bond> bonds = detect_bonds(atoms);

    srand(time(nullptr));
    for(auto& atom : atoms) {
        double v_rms = sqrt(0.831446 * 10.0 / atom.mass);
        atom.velocity.x = v_rms * (rand() / (double)RAND_MAX - 0.5) * 2.0;
        atom.velocity.y = v_rms * (rand() / (double)RAND_MAX - 0.5) * 2.0;
        atom.velocity.z = v_rms * (rand() / (double)RAND_MAX - 0.5) * 2.0;
    }

    const int screenwidth = 1000;
    const int screenheight = 700;
    InitWindow(screenwidth, screenheight, "Molsim Engine v0.5 - 1CRN");
    SetWindowPosition(0, 0);
    
    Camera3D camera = {0};
    camera.position = Vector3{15.0f, 12.0f, 15.0f};
    camera.target = Vector3{5.0f, 2.0f, 5.0f}; 
    camera.up = Vector3{0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);
    double dt = 0.001;
    double target_temp = 300.0;
    int step_counter = 0;
    int visual_scale = 1;

    while(!WindowShouldClose()) {
        if (IsKeyPressed(KEY_UP)) target_temp += 10.0;
        if (IsKeyPressed(KEY_DOWN)) target_temp -= 10.0;
        if (IsKeyPressed(KEY_T)) target_temp = (target_temp > 311.0) ? 310.0 : 313.0; 
        if (IsKeyPressed(KEY_F)) ToggleFullscreen();

        step_counter++;
        if(step_counter % 10 == 0) {
            apply_thermostat(atoms, target_temp);
        }

        for(int step = 0; step < 10; step++) {
            velocity_verlet_step(atoms, dt);
        }

        UpdateCamera(&camera, CAMERA_FREE);
        BeginDrawing();
        ClearBackground(Color{2, 2, 10, 255});  
        BeginMode3D(camera);
        DrawGrid(50, 2.0f); 
        DrawCubeWires(Vector3{0,0,0}, 40.0f, 40.0f, 40.0f, Color{60, 60, 80, 100});


        for(const auto& atom: atoms) {
            Color atomColor;
            float radius;
            char first_letter = atom.type[0];
            
            if(first_letter == 'C') {
                atomColor = Color{80, 80, 80, 255};
                radius = 0.4f;
            } else if(first_letter == 'N') {
                atomColor = Color{50, 100, 255, 255};
                radius = 0.35f;
            } else if(first_letter == 'O') {
                atomColor = Color{255, 60, 60, 255};
                radius = 0.35f;
            } else if(first_letter == 'S') {
                atomColor = Color{255, 220, 30, 255};
                radius = 0.5f;
            } else if(first_letter == 'H') {
                atomColor = Color{220, 220, 220, 255};
                radius = 0.2f;
            } else {
                atomColor = PINK;
                radius = 0.3f;
            }

            DrawSphere(Vector3{
                (float)(atom.position.x * visual_scale),
                (float)(atom.position.y * visual_scale), 
                (float)(atom.position.z * visual_scale)
            }, radius, atomColor);
        }

        for(const auto& bond : bonds) {
            Vec3 p1 = atoms[bond.atom1].position;
            Vec3 p2 = atoms[bond.atom2].position;
            
            DrawLine3D(
                {(float)p1.x, (float)p1.y, (float)p1.z},
                Vector3{(float)p2.x, (float)p2.y, (float)p2.z},
                Color{180, 180, 200, 40}  
            );
        }

        EndMode3D();
        
        double current_t = compute_temperature(atoms);
        DrawText("MolSim Engine v0.5 - 1CRN Crambin", 10, 10, 20, Color{200, 200, 200, 255});
        DrawText(TextFormat("Temp: %.1f K | Target: %.0f K", current_t, target_temp), 10, 35, 16, Color{150, 150, 150, 255});
        DrawText(TextFormat("%d atoms | %d bonds", atoms.size(), bonds.size()), 10, 55, 16, Color{150, 150, 150, 255});
        
        EndDrawing();
    }
    CloseWindow();
    return 0;
}