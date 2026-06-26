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
/*
    for(int x = 0 ; x <  5 ; x++)
    {
        for(int y = 0 ; y < 5 ; y++){
            create_atom(
                atoms,
                "C",

                Vec3(
                    x * 4.0 +(rand()/(double)RAND_MAX - 0.5 )*0.3,
                    y * 4.0 +(rand()/(double)RAND_MAX - 0.5 )*0.3,
                    (rand()/(double)RAND_MAX - 0.5 )*0.3
                ),

            12.0,
            0.1904,
            3.40,
            0.0
            );
        }
    }

    for(int x = 0 ; x < 5 ; x++)
    {
        for(int y = 0 ; y < 5 ; y++){

            create_atom(

                atoms,
                "O",

                Vec3(
                    x * 4.0 + (rand()/(double)RAND_MAX - 0.5)*0.3,
                    y * 4.0 + (rand()/(double)RAND_MAX - 0.5)*0.3,
                    5.0 + (rand()/(double)RAND_MAX - 0.5)*0.3
                ),

                16.0,
                0.2092,
                2.96,
                0.0
            );
        }
    }
*/
/*
    srand(time(nullptr));
    for(auto& atom : atoms) {
        double v_rms = sqrt(0.831446 * 310.0 / atom.mass);
        atom.velocity.x = v_rms * (rand() / (double)RAND_MAX - 0.5) * 2.0;
        atom.velocity.y = v_rms * (rand() / (double)RAND_MAX - 0.5) * 2.0;
        atom.velocity.z = v_rms * (rand() / (double)RAND_MAX - 0.5) * 2.0;

    }
*/
    std::cout << "Created " << atoms.size() << " atoms\n";
    for(int i = 0; i < atoms.size(); i++){
        std::cout << "Atom " << i << " (" << atoms[i].type << "): x=" << atoms[i].position.x 
                  << " y=" << atoms[i].position.y << " charge=" << atoms[i].charge << "\n";
    }

   

    const int screenwidth = 1000;
    const int screenheight = 700;
    InitWindow(screenwidth,screenheight, "Molsim Engine  v0.3 - 10 Atoms");
    
    
    Camera3D camera = {0};
    camera.position = Vector3{10.0f, 10.0f, 10.0f};
    camera.target = Vector3{0.0f, 0.0f, 0.0f};
    camera.up = Vector3{0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);
    double dt = 0.001;
    double target_temp = 5000ff.0;
    int step_counter = 0;
    int visual_scale = 1;
    

    while(!WindowShouldClose()){

        if (IsKeyPressed(KEY_UP)) target_temp += 10.0;
        if (IsKeyPressed(KEY_DOWN)) target_temp -= 10.0;
        if (IsKeyPressed(KEY_T)) target_temp= (target_temp > 311.0) ? 310.0 : 313.0 ; 
        if(IsKeyPressed(KEY_F)){ToggleFullscreen();}

        step_counter++;
        if(step_counter % 10 == 0){
            apply_thermostat(atoms,target_temp);
            
        }
        static int frameCounter = 0;
        frameCounter++;

        if(frameCounter % 60 == 0){
        std::cout
            << "Pos: "
            << atoms[0].position.x << " "
            << atoms[0].position.y << " "
            << atoms[0].position.z
            << " | Vel: "
            << atoms[0].velocity.x << " "
            << atoms[0].velocity.y << " "
            << atoms[0].velocity.z
            << std::endl;
         }

        for(int step = 0 ; step < 10 ; step++){
            velocity_verlet_step(atoms , dt);
        }

        UpdateCamera(&camera , CAMERA_FREE);
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode3D(camera);

        DrawGrid(100 , 5.0f);

        DrawCubeWires(
            Vector3{0,0,0},
            40.0f,
            40.0f,
            40.0f,
            GREEN
                );

        for(const auto& atom: atoms){
            Color atomColor;
            float radius;
            
            char first_letter = atom.type[0];
            if (first_letter == 'C'){
                atomColor = DARKGRAY;
                radius = 0.6f;
            }else if (first_letter == 'N'){
                atomColor = BLUE;
                radius = 0.5f;
            }else if (first_letter == 'O'){
                atomColor = RED;
                radius = 0.5f;
            }else if (first_letter == 'S'){
                atomColor = YELLOW;
                radius = 0.7f;
            }else if (first_letter == 'H'){
                atomColor = WHITE;
                radius = 0.3f;
            }else {
                atomColor = PINK;
                radius = 0.5f;
            }

            DrawSphere(Vector3{
                (float)(atom.position.x * visual_scale),
                (float)(atom.position.y * visual_scale), 
                (float)(atom.position.z * visual_scale)
            } , 
            radius, 
            atomColor);
        }
        EndMode3D();
        
        DrawText("MolSim Engine v0.4 - 1CRN (Crambin)", 10, 10, 24, WHITE);
        DrawText(TextFormat("%d atoms | PDB loaded", atoms.size()), 10, 40, 18, LIGHTGRAY);
        DrawText("Drag mouse to orbit | Scroll to zoom", 10, screenheight - 30, 16, GRAY);

        double current_t = compute_temperature(atoms);
        DrawText(TextFormat("Target : %.0f K (%.1f)" , target_temp , target_temp - 273.15 ) , 10 ,70 ,18 , LIGHTGRAY);
        DrawText(TextFormat("Current %.1f K  " , current_t) , 10 ,90 , 18 , LIGHTGRAY);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}