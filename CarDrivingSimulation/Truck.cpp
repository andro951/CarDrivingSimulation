
#include "Truck.h"
#include "Car.h"

class Truck : Car {
private:


public:
	float GetGasTankCapacity() override {
		return 30;
	}
	float AccelerationStrength() override {
		return 35;
	}
	float BreakingStrength() override {
		return 80;
	}
	float GetMaxTurningAngle() override {
		return 5 * PI / 36;//25 degrees
	}
	float GetAxleDistance() override {
		return 10;
	}
};