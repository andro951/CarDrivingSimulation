#pragma once
#include <vector>
#include "Vehicle.h"

using namespace std;

class Vehicle;

class CarManager {
private:
	vector<unique_ptr<Vehicle>> cars;
	CarManager();
	CarManager(const CarManager& other) = delete;
	CarManager& operator=(const CarManager& other) = delete;
	~CarManager();

public:
	/// <summary>
	/// When first called, this function will create a new instance of CarManager.  Subsequent calls will return the same instance.
	/// Only one instance of CarManager can exist at a time.
	/// </summary>
	/// <returns></returns>
	static CarManager& GetInstance();
	
	void Setup();
	void Cleanup();
	int GetCarCount() const;
	template <typename VehicleType>
	VehicleType& CreateVehicle() {
		//Make a smart pointer (unique_ptr).  unique_ptr can not be copied, only moved.
		unique_ptr<Vehicle> vehicle = make_unique<VehicleType>();

		//Move the smart pointer into the vector.
		cars.push_back(std::move(vehicle));

		//Get a reference to the Vehicle object in the vector.
		VehicleType& vehicleType = static_cast<VehicleType&>(*cars.back());
		vehicleType.Setup();

		return vehicleType;
	}
};