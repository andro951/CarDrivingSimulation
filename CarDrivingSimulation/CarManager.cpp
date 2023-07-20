#include "CarManager.h"
#include <Windows.h>
#include "LogManager.h"

//CarManager carManager;
CarManager& CarManager::GetInstance() {
	//static causes the instance to be created only once for each time GetInstance() is called.
	static CarManager instance;
	return instance;
}

CarManager::CarManager() {
	Setup();
}
CarManager::~CarManager() {
	Cleanup();
}

void CarManager::Setup() {
	CreateLogFolders();
}
void CarManager::Cleanup() {
	//Not used yet.
}
int CarManager::GetCarCount() const {
	return cars.size();
}