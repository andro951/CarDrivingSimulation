#pragma once
#include "CarMath.h"
#include "SimulationSystem.h"
#include "Vehicle.h"

class ElectricVehicle {
protected:
	virtual bool RequirementsMetToChargeBattery() const = 0;

public:
	int MilesRemaining() const {
		//Not finished
	}
	float GallonsInTank(const Vehicle& vehicle) {
		return WhattHoursToGallonsOfGas(vehicle.storedEnergy);
	}
	float GetGasTankCapacity(const Vehicle& vehicle) const {
		return WhattHoursToGallonsOfGas(vehicle.storedEnergy);
	}
	bool CanFillTank(const Vehicle& vehicle) const {
		return vehicle.storedEnergy < vehicle.energyCapacity && RequirementsMetToChargeBattery();
	}

	/// <summary>
	/// Fills the gas tank.  Meant to be called every update while filling the tank.
	/// </summary>
	/// <param name="fillRate">Gallons per second.</param>
	/// <param name="fillDuration">How long the tank has been filled.</param>
	/// <returns>The amount of gallons filled.</returns>
	virtual float FillTank(Vehicle& vehicle, float fillRate, float fillDuration = updateDuration) {
		float gallonsInTank = WhattHoursToGallonsOfGas(vehicle.storedEnergy);
		float gallonsFilled = fillRate * fillDuration;
		float tankSpace = GetGasTankCapacity(vehicle) - gallonsInTank;
		if (tankSpace < gallonsFilled)
			gallonsFilled = tankSpace;

		float wattHoursFilled = GallonsOfGasToWattHours(gallonsFilled);
		vehicle.storedEnergy += wattHoursFilled;

		return gallonsFilled;
	}
	float GetGasInTank(const Vehicle& vehicle) const {
		return WhattHoursToGallonsOfGas(vehicle.storedEnergy);
	}
};