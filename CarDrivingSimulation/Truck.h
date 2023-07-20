#pragma once
#include "Vehicle.h"

class Truck : public Vehicle {
private:


public:
	float GetGasTankCapacity() override;
	float AccelerationStrength() override;
	float BreakingStrength() override;
	float GetMaxTurningAngle() override;
	float GetAxleDistance() override;
	float GetCarWindAndFrictionMultiplier() override;
	float GetWeight() override;
	string GetName() override;
};