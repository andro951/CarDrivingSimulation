#include <iostream>
#include "Vehicle.h"
#include "Truck.h"
#include "CarManager.h"
#include "CarMath.h"
#include "SimulationSystem.h"
#include "ElectricCar.h"
#include "GasTruck.h"

using namespace std;

/*TODO:
ElectricVehicle
    MilesRemaining()
    Change everything in it to be battery/electric instead of the copied gas stuff.
    

GasVehicle
    MilesRemaining()

Need to fill up each car or set their storedEnergy to something at the beginning of main()

Create a menu for controlling the vehicles that allows for using each of the controls and allows them to wait (update) for some amount of time.
*/

int main() {
    //Create the car manager so that it runs it's setup function.
    CarManager::GetInstance();
    ElectricCar& car = CarManager::GetInstance().CreateVehicle<ElectricCar>();
    GasTruck& car2 = CarManager::GetInstance().CreateVehicle<GasTruck>();
    car.StartEngine();
    car.SetGasPedalPosition(1);
    car.SetSteeringWheelPosition(1);
    car2.StartEngine();
    car2.SetGasPedalPosition(1);
    car2.SetSteeringWheelPosition(1);
    float seconds = 0;
    float tickInterval = updateDuration;
    for (int i = 0; i < 600; i++) {
        car.Update(tickInterval);
        string carInfo = "Seconds: " + to_string(seconds) + ", " + car.GetAllInfo();
        car.LogCarInfo(carInfo);
        cout << carInfo << endl;

        car2.Update(tickInterval);
        string car2Info = "Seconds: " + to_string(seconds) + ", " + car2.GetAllInfo();
        car2.LogCarInfo(car2Info);
        cout << car2Info << endl;

        seconds += tickInterval;
	}

    car.SetGasPedalPosition(0);
    car2.SetGasPedalPosition(0);
    for (int i = 0; i < 600; i++) {
        car.Update(tickInterval);
        string carInfo = "Seconds: " + to_string(seconds) + ", " + car.GetAllInfo();
        car.LogCarInfo(carInfo);
        cout << carInfo << endl;

        car2.Update(tickInterval);
        string car2Info = "Seconds: " + to_string(seconds) + ", " + car2.GetAllInfo();
        car2.LogCarInfo(car2Info);
        cout << car2Info << endl;

        seconds += tickInterval;
    }

    car.SetGasPedalPosition(1);
    car2.SetGasPedalPosition(1);
    for (int i = 0; i < 600; i++) {
        car.Update(tickInterval);
        string carInfo = "Seconds: " + to_string(seconds) + ", " + car.GetAllInfo();
        car.LogCarInfo(carInfo);
        cout << carInfo << endl;

        car2.Update(tickInterval);
        string car2Info = "Seconds: " + to_string(seconds) + ", " + car2.GetAllInfo();
        car2.LogCarInfo(car2Info);
        cout << car2Info << endl;

        seconds += tickInterval;
    }

    car.SetGasPedalPosition(0);
    car.SetBreakPedalPosition(1);
    car.SetSteeringWheelPosition(-1);
    car2.SetGasPedalPosition(0);
    car2.SetBreakPedalPosition(1);
    car2.SetSteeringWheelPosition(-1);
    for (int i = 0; i < 600; i++) {
        car.Update(tickInterval);
        string carInfo = "Seconds: " + to_string(seconds) + ", " + car.GetAllInfo();
        car.LogCarInfo(carInfo);
        cout << carInfo << endl;

        car2.Update(tickInterval);
        string car2Info = "Seconds: " + to_string(seconds) + ", " + car2.GetAllInfo();
        car2.LogCarInfo(car2Info);
        cout << car2Info << endl;

        seconds += tickInterval;
    }
}
