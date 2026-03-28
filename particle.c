#include "particle.h"
#include "vector.h"
#include <math.h>
#define K 100 //coloumb's constant, can be adjusted for simulation scale

particle create_particle(vector position, vector velocity, vector acceleration, float charge, float mass) {
    particle p;
    p.position = position;
    p.velocity = velocity;
    p.acceleration = acceleration;
    p.charge = charge;
    p.mass = mass;
    return p;
}
void particle_update(particle* p, vector force) {
    p->acceleration = vector_scale(force, 1.0f / p->mass);
    p->velocity = vector_add(p->velocity, p->acceleration);
    p->position = vector_add(p->position, p->velocity);
}
vector net_force(particle* p1, particle* p2){
    vector r = vector_subtract(p2->position, p1->position);
    float distance = vector_length(r);
    if (distance == 0) {
        return create_vector(0, 0);
    }
    float min_distance = 15.0f;
    float calc_distance = distance;
    if (calc_distance < min_distance) {
        calc_distance = min_distance;
    }
    float force_size = K*(p1->charge * p2->charge)/(calc_distance * calc_distance);
    vector force_direction = vector_normalize(r);
    vector force = vector_scale(force_direction, force_size);
    return force;
}