#pragma once
#include <cmath>

const float PI = 3.14159265358979323846f;

/// <summary>
/// Normalize the angle to the range [0, 2 pi] radians.
/// </summary>
/// <param name="angle"></param>
/// <returns></returns>
float NormalizeAngle(float angle);

float RadiansToDegrees(float radians);