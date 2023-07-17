#include <iostream>
#include "Car.h"

/*TODO:
Troubeshoot acceleration issues
Speed needs to be in MPH (3600 seconds / hr)
Position needs to be in feet (5280 ft/mile)
After speed/position units are updated, test max speed of the car again to about 200 mph
Make a new overridable getter variable for windAndFriction()
*/

int main() {
    Car car;
    car.StartEngine();
    car.SetGasPedalPosition(1);
    car.SetSteeringWheelPosition(1);
    for (int i = 0; i < 100; i++) {
		car.Update(0.1);
		std::cout << "Speed: " << car.GetSpeed() << ", Position: " << car.GetPosition().first << ", " << car.GetPosition().second 
            << ", Facing Direction: " << car.GetFacingDirection() << std::endl;
	}
}
