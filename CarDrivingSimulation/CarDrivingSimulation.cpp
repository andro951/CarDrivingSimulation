#include <iostream>
#include "Car.h"
#include "Truck.h"
#include "CarManager.h"
#include "CarMath.h"

using namespace std;

/*TODO:
Speed needs to be in MPH (3600 seconds / hr)
Position needs to be in feet (5280 ft/mile)
After velocity/position units are updated, test max velocity of the car again to about 200 mph
Wind resistance and friction is way too strong.  Needs to be reduced.
*/

int main() {
    //Create the car manager so that it runs it's setup function.
    CarManager::GetInstance();
    Car car;
    Truck car2;
    car.StartEngine();
    car.SetGasPedalPosition(1);
    car.SetSteeringWheelPosition(1);
    car2.StartEngine();
    car2.SetGasPedalPosition(1);
    car2.SetSteeringWheelPosition(1);
    float seconds = 0;
    float tickInterval = 0.1f;
    for (int i = 0; i < 100; i++) {
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
    for (int i = 0; i < 100; i++) {
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