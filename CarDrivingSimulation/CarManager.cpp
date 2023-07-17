#include "CarManager.h"
#include <Windows.h>
#include "LogManager.h"

CarManager carManager;

void CarManager::Setup() {
	CreateLogFolders();
}
void CarManager::AddCar(Car& car) {
	cars.push_back(car);
}
int CarManager::GetCarCount() const {
	return cars.size();
}