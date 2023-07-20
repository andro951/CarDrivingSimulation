#include "CarMath.h"

const float PI = 3.14159265358979323846f;

float typicalEnergyContentOfGas = 34.0f;//MJ/L
float whatHoursPerMegaJoul = 277.77777777777777777777777777778f;
float litersPerGallon = 3.78541f;

float NormalizeAngle(float angle) {
	if (angle >= 0.0f && angle <= 2 * PI)
		return angle;

	//Take the modulus of the angle with respect to 2 pi radians.
	//If the angle is negative, the result of fmod will be negative.
	float normalizedAngle = fmod(angle, 2 * PI);
	if (angle < 0.0f)
		normalizedAngle += 2 * PI;

	return normalizedAngle;
}

float RadiansToDegrees(float angle) {
	return angle * 180 / PI;
}

float WhattHoursToGallonsOfGas(float whattHours) {
	return whattHours / (typicalEnergyContentOfGas * whatHoursPerMegaJoul * litersPerGallon);
}
float GallonsOfGasToWattHours(float gallonsOfGas) {
	return gallonsOfGas * typicalEnergyContentOfGas * whatHoursPerMegaJoul * litersPerGallon;
}