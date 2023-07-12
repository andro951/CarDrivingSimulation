#include "Car.h"

//Car Model Properties
float Car::GetGasTankCapacity() {
    return 20;
}
float Car::AccelerationStrength() {
    return 50;
}
float Car::BreakingStrength() {
    return 100;
}
float Car::GetMaxTurningAngle() {
    return PI / 6;//30 degrees
}
float Car::GetAxleDistance() {
    return 8;
}
//Car Model Properties

void Car::Update(const float secondsSinceLastUpdate) {
    UpdateCarPositionAndFacingDirection(secondsSinceLastUpdate);

    //Update the speed after the position to have a small amount of lag to help simulate inertia.
    UpdateSpeed(secondsSinceLastUpdate);
}
void Car::UpdateCarPositionAndFacingDirection(const float secondsSinceLastUpdate) {
    float distance = speed * secondsSinceLastUpdate;
    float axleDistance = GetAxleDistance();
    float turningAngle = GetTurningAngle();

    //When a car turns, it turns in a circle.
    //turnDiameter is the diameter of that circle.
    float turnDiameter = axleDistance * 2 * PI / turningAngle;

    //turnFraction is the fraction of the whole turn circle that the car turns in this update tick.
    float turnFraction = distance / turnDiameter;

    //turnAngle is the angle at the center of the turn circle.  The right triangle is formed with the hypotenuse from the center of the circle
    //to the car's new position, and the adjacent side is the car's old position minus the relative change in x.
    float turnAngle = turnFraction * 2 * PI;

    //turnRadius is the radius of the turn circle.
    float turnRadius = turnDiameter / PI;

    //relativeChangeInX and relativeChangeInY are the change in x and y relative to the car's old position.
    //They are calculated assuming the car's facing direction is 0, so they must be rotated to match the car's actual facing direction.
    float relativeChangeInY = sin(turnAngle) * turnRadius;
    float relativeChangeInX = turnRadius * (1 - cos(turnAngle));

    //Rotate the relative change in x and y to match the car's facing direction.
    float cosFacingDirection = cos(facingDirection);
    float sinFacingDirection = sin(facingDirection);
    float changeInX = relativeChangeInX * cosFacingDirection - relativeChangeInY * sinFacingDirection;
    float changeInY = relativeChangeInX * sinFacingDirection + relativeChangeInY * cosFacingDirection;

    //Update the car's position and facing direction.
    position.first += changeInX;
    position.second += changeInY;
    facingDirection += turnAngle;
}
void Car::UpdateSpeed(const float secondsSinceLastUpdate) {
    float acceleration = GetAcceleration(secondsSinceLastUpdate);
    speed += acceleration * secondsSinceLastUpdate;
}
float Car::GetAcceleration(const float secondsSinceLastUpdate) {
    float acceleration = 0;
    //Acceleration from gas pedal
    if (engineRunning)
        acceleration += AccelerationStrength() * gasPedalPosition;

    //Breaking, wind resistance and friction should only ever cause deceleration.
    //If the car is moving forward and the break pedal is pressed, the car should slow down.
    //The magnitude of speed should never increase from breaking.

    float speedFromAcceleration = acceleration * secondsSinceLastUpdate;
    float newSpeedAccelerationOnly = speed + speedFromAcceleration;

    if (newSpeedAccelerationOnly != 0) {
        float accelerationSign = acceleration >= 0 ? 1 : -1;

        //Invert acceleration if acceleration is negative.
        acceleration *= accelerationSign;

        //Wind resistance and friction.
        float deceleration = speed * 0.25;

        //Deceleration from breaking
        deceleration += BreakingStrength() * breakPedalPosition;

        if (deceleration > acceleration) {
            deceleration -= acceleration;
            if (speed < 0)
                deceleration *= -1;

            float speedFromDeceleration = deceleration * secondsSinceLastUpdate;
            if (speedFromDeceleration * -1 > speed) {
                acceleration = speed * -1 / secondsSinceLastUpdate;
            }
            else {
				acceleration = deceleration;
            }
        }
        else {
            acceleration -= deceleration;
            acceleration *= accelerationSign;
        }
    }

    return acceleration;
}
float Car::GetTurningAngle() {
    return GetMaxTurningAngle() * steeringWheelPosition;
}
float Car::GetSpeed() {
    return speed;
}
std::pair<float, float> Car::GetPosition() {
    return position;
}
float Car::GetFacingDirection() {
    return facingDirection;
}
void Car::StartEngine() {
    engineRunning = true;
}
void Car::StopEngine() {
    engineRunning = false;
}
void Car::ShiftToReverse() {
    reverse = true;
}
void Car::ShiftToDrive() {
	reverse = false;
}
void Car::SetGasPedalPosition(float value) {
    if (value >= 0 && value <= 1)
        gasPedalPosition = value;
}
void Car::SetBreakPedalPosition(float value) {
    if (value >= 0 && value <= 1)
        breakPedalPosition = value;
}
void Car::SetSteeringWheelPosition(float value) {
    if (value >= -1 && value <= 1)
        steeringWheelPosition = value;
}