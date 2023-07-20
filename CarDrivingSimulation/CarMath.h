#pragma once
#include <cmath>

extern const float PI;

extern float typicalEnergyContentOfGas;//MJ/L
extern float whatHoursPerMegaJoul;
extern float litersPerGallon;

/// <summary>
/// Normalize the angle to the range [0, 2 pi] radians.
/// </summary>
/// <param name="angle"></param>
/// <returns></returns>
float NormalizeAngle(float angle);

float RadiansToDegrees(float radians);

float WhattHoursToGallonsOfGas(float whattHours);
float GallonsOfGasToWattHours(float gallonsOfGas);