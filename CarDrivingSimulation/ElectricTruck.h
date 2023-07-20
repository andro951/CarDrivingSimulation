#pragma once
#include "ElectricVehicle.h"
#include "Truck.h"

class ElectricTruck : public Truck, public ElectricVehicle {
	bool RequirementsMetToChargeBattery() const override;
};