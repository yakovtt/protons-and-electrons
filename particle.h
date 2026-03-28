#pragma once
#include "vector.h"

typedef struct {
    vector position;
    vector velocity;
    vector acceleration;
    float charge;
    float mass;
} particle;

particle create_particle(vector position, vector velocity, vector acceleration, float charge, float mass);
void particle_update(particle* p, vector force);
vector net_force(particle* p1, particle* p2);
