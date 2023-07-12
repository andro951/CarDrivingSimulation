#include <iostream>
#include "Car.h"

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