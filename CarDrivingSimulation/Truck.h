#pragma once
#include "Car.h"

class Truck : public Car {
private:


public:
	float GetGasTankCapacity() override;
	float AccelerationStrength() override;
	float BreakingStrength() override;
	float GetMaxTurningAngle() override;
	float GetAxleDistance() override;
	float GetCarWindAndFrictionMultiplier() override;
	string GetName() override;
};