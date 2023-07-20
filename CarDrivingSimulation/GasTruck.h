#pragma once
#include "GasVehicle.h"
#include "Truck.h"

class GasTruck : public Truck, public GasVehicle {
	bool RequirementsMetToFillTank() const override;
};