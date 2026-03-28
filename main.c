#include "raylib.h"
#include "particle.h"
#include "vector.h"
#include <stdlib.h>
#include <math.h>

int main(void){
    int screenWidth = 800;
    int screenHeight = 600;
    int numElectrons = 64;

    InitWindow(screenWidth, screenHeight, "Particle Simulation");
    particle nucleus = create_particle(create_vector(screenWidth/2, screenHeight/2), create_vector(0, 0), create_vector(0, 0), -5, 10000.0f);
    particle electrons[numElectrons];
    vector net_forces[numElectrons];
    for (int i = 0; i < numElectrons; i++) {
        vector start_pos = create_vector(rand() % screenWidth, rand() % screenHeight);

        vector r_vec = vector_subtract(start_pos, nucleus.position);
        vector r_dir = vector_normalize(r_vec);

        vector tangent = create_vector(-r_dir.y, r_dir.x);

        float orbital_speed = 12.0f;
        vector start_vel = vector_scale(tangent, orbital_speed);

        // 5. Create the electron with this sideways velocity
        electrons[i] = create_particle(start_pos, start_vel, create_vector(0, 0), 3.0f, 1.0f);
    }
    SetTargetFPS(360);
    while (!WindowShouldClose()) {

        for (int i = 0; i < numElectrons; i++) {
            net_forces[i] = create_vector(0, 0);
        }
        for (int i = 0; i < numElectrons; i++) {
            vector nuc_force = net_force(&nucleus, &electrons[i]);
            net_forces[i] = vector_add(net_forces[i], nuc_force);

            for(int j = i + 1; j < numElectrons; j++) {
                vector force_on_j = net_force(&electrons[i], &electrons[j]);

                net_forces[j] = vector_add(net_forces[j], force_on_j);
                net_forces[i] = vector_subtract(net_forces[i], force_on_j);
            }
        }
        float max_radius = 250.0f;
        float boundary_restitution = 0.9f;

        for(int i = 0; i < numElectrons; i++) {
            particle_update(&electrons[i], net_forces[i]);
            electrons[i].velocity = vector_scale(electrons[i].velocity, 0.99f);

            vector r_vec = vector_subtract(electrons[i].position, nucleus.position);
            float dist = vector_length(r_vec);
            if(dist > max_radius) {
                vector n = vector_normalize(r_vec);
                electrons[i].position = vector_add(nucleus.position, vector_scale(n, max_radius));
                
                float v_dot_n = vector_dot(electrons[i].velocity, n);

                if(v_dot_n > 0) {
                    vector bounce = vector_scale(n, (1.0f + boundary_restitution) * v_dot_n);
                    electrons[i].velocity = vector_subtract(electrons[i].velocity, bounce);
                }
            }
            
        }
        BeginDrawing();
        //ClearBackground(DARKGRAY);
        DrawRectangle(0, 0, screenWidth, screenHeight, (Color){80, 80, 80, 15});
        DrawCircleV((Vector2){nucleus.position.x, nucleus.position.y}, 10, RED);
        for (int i = 0; i < numElectrons; i++) {
            DrawCircleV((Vector2){electrons[i].position.x, electrons[i].position.y}, 5, BLUE);
        }
        EndDrawing();
        
    }
    CloseWindow();
    return 0;
}
