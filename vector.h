#pragma once

typedef struct {
    float x;
    float y;
} vector;

vector create_vector(float x, float y);
vector vector_add(vector a, vector b);
vector vector_subtract(vector a, vector b);
vector vector_scale(vector v, float scalar);
float vector_length(vector v);
vector vector_normalize(vector v);
float vector_dot(vector a, vector b);