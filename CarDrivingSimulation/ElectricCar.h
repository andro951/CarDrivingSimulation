#pragma once
#include "ElectricVehicle.h"
#include "Car.h"

class ElectricCar : public Car, public ElectricVehicle {
	bool RequirementsMetToChargeBattery() const override;
};