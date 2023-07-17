#include "Truck.h"

float Truck::GetGasTankCapacity() {
	return 30.0f;
}
float Truck::AccelerationStrength() {
	return 70.0f;
}
float Truck::BreakingStrength() {
	return 80.0f;
}
float Truck::GetMaxTurningAngle() {
	return 5.0f * PI / 36.0f;//25 degrees
}
float Truck::GetAxleDistance() {
	return 10.0f;
}
float Truck::GetCarWindAndFrictionMultiplier() {
	return 0.5f;
}
string Truck::GetName() {
	return "Truck";
}