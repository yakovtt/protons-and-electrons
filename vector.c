#include "vector.h"
#include <math.h>

vector create_vector(float x, float y) {
    vector v;
    v.x = x;
    v.y = y;
    return v;
}
vector vector_add(vector a, vector b) {
    return create_vector(a.x + b.x, a.y + b.y);
}
vector vector_subtract(vector a, vector b) {
    return create_vector(a.x - b.x, a.y - b.y);
}
vector vector_scale(vector v, float scalar) {
    return create_vector(v.x * scalar, v.y * scalar);
}
float vector_length(vector v) {
    return sqrtf(v.x * v.x + v.y * v.y);
}
vector vector_normalize(vector v) {
    float length = vector_length(v);
    if (length == 0) {
        return create_vector(0, 0);
    }
    return vector_scale(v, 1.0f / length);
}
float vector_dot(vector a, vector b) {
    return a.x * b.x + a.y * b.y;
} 