#include <iostream>
#include "Car.h"
#include "CarManager.h"
#include "CarMath.h"

using namespace std;

/*TODO:
Troubeshoot acceleration issues
Speed needs to be in MPH (3600 seconds / hr)
Position needs to be in feet (5280 ft/mile)
After speed/position units are updated, test max speed of the car again to about 200 mph
Make a new overridable getter variable for windAndFriction()
*/

int main() {
    //Create the car manager so that it runs it's setup function.
    CarManager::GetInstance();
    Car car;
    Car car2;
    car.StartEngine();
    car.SetGasPedalPosition(1);
    car.SetSteeringWheelPosition(1);
    float seconds = 0;
    float tickInterval = 0.1f;
    for (int i = 0; i < 100; i++) {
		car.Update(tickInterval);
		cout << "Seconds: " << seconds << ", Speed: " << car.GetSpeed() << ", Position: " << car.GetPosition().first << ", " << car.GetPosition().second
            << ", Facing Direction: " << car.GetFacingDirection() << "(" << round(RadiansToDegrees(car.GetFacingDirection())) << " deg)" << endl;

        seconds += tickInterval;
	}

    car.SetGasPedalPosition(0);
    for (int i = 0; i < 100; i++) {
        car.Update(tickInterval);
        cout << "Seconds: " << seconds << ", Speed: " << car.GetSpeed() << ", Position: " << car.GetPosition().first << ", " << car.GetPosition().second
            << ", Facing Direction: " << car.GetFacingDirection() << "(" << round(RadiansToDegrees(car.GetFacingDirection())) << " deg)" << endl;

        seconds += tickInterval;
    }

    /*
    car.SetGasPedalPosition(0);
    car.SetBreakPedalPosition(1);
    for (int i = 0; i < 100; i++) {
        car.Update(tickInterval);
        std::cout << "Seconds: " << seconds << ", Speed: " << car.GetSpeed() << ", Position: " << car.GetPosition().first << ", " << car.GetPosition().second
            << ", Facing Direction: " << car.GetFacingDirection() << std::endl;

        seconds += tickInterval;
    }

    car.ShiftToReverse();
    car.SetBreakPedalPosition(0);
    car.SetGasPedalPosition(1);
    for (int i = 0; i < 100; i++) {
        car.Update(tickInterval);
        std::cout << "Seconds: " << seconds << ", Speed: " << car.GetSpeed() << ", Position: " << car.GetPosition().first << ", " << car.GetPosition().second
            << ", Facing Direction: " << car.GetFacingDirection() << std::endl;

        seconds += tickInterval;
    }

    car.SetGasPedalPosition(0);
    car.SetBreakPedalPosition(1);
    for (int i = 0; i < 100; i++) {
        car.Update(tickInterval);
        std::cout << "Seconds: " << seconds << ", Speed: " << car.GetSpeed() << ", Position: " << car.GetPosition().first << ", " << car.GetPosition().second
            << ", Facing Direction: " << car.GetFacingDirection() << std::endl;

        seconds += tickInterval;
    }
    */
}