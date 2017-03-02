#ifndef UTILITY_H
#define UTILITY_H

#include "Game.h"
#include <iostream>
#include <random>
#include <iomanip>

constexpr float RADTODEGREE = 57.295779513082320876798154814105;
constexpr float SIN45 = 0.70710678118; //Sinus of 45 degrees, also length of unit vector.x or .y
constexpr float PI = 3.14159265359;

static std::mt19937 mt(1337);
static float random_float(float lower, float higher) {
    std::uniform_real_distribution<float> dist(lower, higher);
    return dist(mt);
}

static float fast_abs(float x){
    int y = (int&)x & 0x7FFFFFFF;
    return (float&)y;
}

static float vecToAngle(const sf::Vector2f& vec){
    if(vec.x == 0.0f && vec.y == 0.0f) return 0.0f;
    float absx = fast_abs(vec.x), absy = fast_abs(vec.y);
    float a = absx > absy ? absy/absx : absx/absy;
    float s = a * a;
    float r = ((-0.0464964749 * s + 0.15931422) * s - 0.327622764) * s * a + a;

    if(absy > absx) r = 1.57079637 - r;
    if(vec.x < 0) r = 3.14159274 - r;
    if(vec.y < 0) r = -r;

    float ang = r*RADTODEGREE + 90.0f;
    if(ang < 0.0f) ang += 360.0f;
    else if(ang > 360.0f) ang -= 360.0f;
    return ang;
}

static sf::Vector2f angleToVec(const float& degree) {
    float rad = (-degree + 90.0f)/RADTODEGREE;
    return sf::Vector2f(cosf(rad), -sinf(rad));
}

static float magnitude(const sf::Vector2f& a) {
    return sqrt(a.x * a.x + a.y * a.y);
}

static sf::Vector2f normalize(const sf::Vector2f& a) {
    float mag = magnitude(a);
    if(mag == 0) return a;
    return a / mag;
}

#endif // UTILITY_H
