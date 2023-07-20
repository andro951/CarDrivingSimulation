#pragma once
#include "GasVehicle.h"
#include "Car.h"

class GasCar : public Car, public GasVehicle {
	bool RequirementsMetToFillTank() const override;
};