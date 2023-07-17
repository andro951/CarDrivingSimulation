#include "CarMath.h"

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