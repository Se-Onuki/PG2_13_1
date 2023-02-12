#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include "Math/Vector2.hpp"

#define functionEasing(start , end, easingVolume, easingType)  easingMove(start, end, easingType(easingVolume))
#define easePlane(number) number


template <class TYPE>
inline TYPE Easing(TYPE start, TYPE end, float volume) {
	return ((start)+((end)-(start)) * (volume));
}

inline float EaseAngles(float angleA, float angleB, float t) {
    float delta = angleB - angleA;

    // Normalize delta angle to be within -pi to pi radians
    delta = fmod(delta + M_PI, 2 * M_PI) - M_PI;
    //Check the range of delta angle
    if (delta > M_PI) {
        delta = 2 * M_PI - delta;
    }
    else if (delta < -M_PI) {
        delta = -2 * M_PI - delta;
    }

    // Perform linear interpolation
    return angleA + delta * t;
}

Vector2 Easing(Vector2 start, Vector2 end, float easingVolume);

unsigned int ColorEasing(unsigned int statColor, unsigned int endColor, float easingVolume);


float easeLinear(float number);

float easeInBack(float x);
float easeOutBack(float x);

float easeInCirc(float x);
float easeOutCirc(float x);

float easeInSine(float x);
float easeOutSine(float x);

float easeInExpo(float x);
float easeOutExpo(float x);

float easeInQuad(float x);
float easeOutQuad(float x);
