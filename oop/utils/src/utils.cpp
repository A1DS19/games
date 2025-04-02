#include "utils.hpp"

bool isEqual(float x, float y) { return fabsf(x - y) < EPSILON; }
bool isGreaterThanOrEqual(float x, float y) { return x > y || x == y; }
bool isLessThanOrEqual(float x, float y) { return x < y || x == y; }
