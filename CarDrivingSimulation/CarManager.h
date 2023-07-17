#pragma once
#include <vector>
#include "Car.h"

using namespace std;

class Car;

class CarManager {
private:
	vector<Car> cars;

public:
	void Setup();
	void AddCar(Car& car);
	int GetCarCount() const;
};

extern CarManager carManager;