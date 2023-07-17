#pragma once
#include <vector>
#include "Car.h"

using namespace std;

class Car;

class CarManager {
private:
	vector<Car> cars;
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
	void AddCar(Car& car);
	int GetCarCount() const;
};

//extern CarManager carManager;