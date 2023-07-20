#include "Car.h"

float Car::GetGasTankCapacity() {
	return 20.0f;
}
float Car::AccelerationStrength() {
	return 50.0f;
}
float Car::BreakingStrength() {
	return 100.0f;
}
float Car::GetMaxTurningAngle() {
	return PI / 6.0f;//30 degrees
}
float Car::GetAxleDistance() {
	return 8.0f;
}
float Car::GetCarWindAndFrictionMultiplier() {
	return 0.25f;
}
float Car::GetWeight() {
	return 3300.0f;
}
string Car::GetName() {
	return "Car";
}