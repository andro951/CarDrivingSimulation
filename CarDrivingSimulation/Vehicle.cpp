#include "Vehicle.h"
#include "LogManager.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Vehicle::Vehicle() {
    id = CarManager::GetInstance().GetCarCount();
}
Vehicle::Vehicle(const Vehicle& other) {
    id = other.id;
}
Vehicle::~Vehicle() {
	Cleanup();
}

#pragma region Vehicle Functions

void Vehicle::Setup() {
    SetupLogs();
}
void Vehicle::Cleanup() {
    CleanupLogs();
}
void Vehicle::Update(const float secondsSinceLastUpdate) {
    UpdateCarPositionAndFacingDirection(secondsSinceLastUpdate);

    float accelerationFromEngine;
    float acceleration = GetAcceleration(secondsSinceLastUpdate, accelerationFromEngine);

    //Update the velocity after the position to have a small amount of lag to help simulate inertia.
    UpdateVelocity(secondsSinceLastUpdate, acceleration);

    ConsumeStoredEnergy(secondsSinceLastUpdate, accelerationFromEngine);

    DoUpdateLogs();
}
void Vehicle::UpdateCarPositionAndFacingDirection(const float secondsSinceLastUpdate) {
    //distance is in feet.  velocity is in miles per hour.  secondsSinceLastUpdate is in seconds.
    //distance = velocity * secondsSinceLastUpdate * 5280 feet per mile * 1 hour per 3600 seconds
    float distance = velocity * secondsSinceLastUpdate * 5280.0f / 3600.0f;
    float axleDistance = GetAxleDistance();
    float turningAngle = GetTurningAngle();

    //Multiplier to manually adjust the turning angle.  The turning angle calculation is likely off from reality somewhere, so introducing this
    //multiplier to help compensate for that.
    float turningMultiplier = 1/PI;

    //When a car turns, it turns in a circle.
    //turnCircumference is the circumference of that circle.
    float turnCircumference = axleDistance * 2.0f * PI / turningAngle * turningMultiplier;

    //turnFraction is the fraction of the whole turn circle that the car turns in this update tick.
    float turnFraction = distance / turnCircumference;

    //turnAngle is the angle at the center of the turn circle.  The right triangle is formed with the hypotenuse from the center of the circle
    //to the car's new position, and the adjacent side is the car's old position minus the relative change in x.
    float turnAngle = turnFraction * 2.0f * PI;

    //turnRadius is the radius of the turn circle.
    float turnRadius = turnCircumference / PI;

    //relativeChangeInX and relativeChangeInY are the change in x and y relative to the car's old position.
    //They are calculated assuming the car's facing direction is 0, so they must be rotated to match the car's actual facing direction.
    float relativeChangeInY = sin(turnAngle) * turnRadius;
    float relativeChangeInX = turnRadius * (1.0f - cos(turnAngle));

    //Rotate the relative change in x and y to match the car's facing direction.
    //facingDirection is negative because turning left is positive and turning right is negative.  The steering wheel position is negative for turning left
    //and positive for turning right.
    //Subtract Pi / 2 to shift the facing direction 90 from North at facingDirection 0 to East.
    //Changing it this way matches the standard method of measuring angles in math, where 0 is East and positive angles are counter-clockwise.
    float cosFacingDirection = cos(-GetFacingDirection() - PI / 2.0f);
    float sinFacingDirection = sin(-GetFacingDirection() - PI / 2.0f);
    float changeInX = relativeChangeInX * cosFacingDirection - relativeChangeInY * sinFacingDirection;
    float changeInY = relativeChangeInX * sinFacingDirection + relativeChangeInY * cosFacingDirection;

    //Update the car's position and facing direction.
    position.first += changeInX;
    position.second += changeInY;
    SetFacingDirection(GetFacingDirection() + turnAngle);
}
void Vehicle::UpdateVelocity(const float secondsSinceLastUpdate, const float acceleration) {
    velocity += acceleration * secondsSinceLastUpdate;
}
void Vehicle::ConsumeStoredEnergy(const float secondsSinceLastUpdate, const float accelerationFromEngine) {
    float energyEfficiency = 0.0003725061f;
    float gravity = 32.174f;//feet per second squared
    storedEnergy -= (accelerationFromEngine * GetWeight() * secondsSinceLastUpdate) / (energyEfficiency * gravity);
    if (storedEnergy < 0.0f)
        storedEnergy = 0.0f;
}
float& Vehicle::GetStoredEnergyRef() {
    return storedEnergy;
}
float Vehicle::GetStoredEnergy() const {
    return storedEnergy;
}
float Vehicle::GetEnergyCapacity() const {
    return energyCapacity;
}
bool Vehicle::CanAccelerate() {
    //Known deficiency: Does not check if the remaining stored energy is enough to accelerate for the full duration of the update tick.
    //This deficiency is acceptable because the update ticks are intended to be very small, so the stored energy should not change much between ticks.
    return engineRunning && gasPedalPosition > 0.0f && storedEnergy > 0.0f;
}
float Vehicle::GetAcceleration(const float secondsSinceLastUpdate, float& accelerationFromEngine) {
    float acceleration = 0;
    //Acceleration from gas pedal
    if (CanAccelerate())
        acceleration += AccelerationStrength() * gasPedalPosition;

    accelerationFromEngine = acceleration;

    //Breaking, wind resistance and friction should only ever cause deceleration.
    //If the car is moving forward and the break pedal is pressed, the car should slow down.
    //The magnitude of velocity should never increase from breaking.

    float speedFromAcceleration = acceleration * secondsSinceLastUpdate;
    float newVelocityAccelerationOnly = velocity + speedFromAcceleration;

    if (newVelocityAccelerationOnly != 0) {
        float accelerationSign = acceleration >= 0.0f ? 1.0f : -1.0f;

        //Invert acceleration if acceleration is negative.
        //Making acceleration positive makes the math easier.
        //deceleration is always going to be positive.
        acceleration *= accelerationSign;

        //Since we are calculating deceleration with both acceleration and deceleration being positive, we use speed instead of velocity.
        float speed = GetSpeed();

        //Wind resistance and friction.
        float deceleration = speed * GetCarWindAndFrictionMultiplier();

        //Deceleration from breaking
        deceleration += BreakingStrength() * breakPedalPosition;

        //If deceleration is greater than acceleration, then the car is slowing down.
        if (deceleration > acceleration) {
            deceleration -= acceleration;
            acceleration = 0;

            //Check if the deceleration will cause the car to reverse directions.
            //If it will, reduce the deceleration to match the speed so that car stops instead of reversing.
            float speedFromDeceleration = deceleration * secondsSinceLastUpdate;
            if (speedFromDeceleration > speed)
                deceleration = speed / secondsSinceLastUpdate;
        }

        acceleration -= deceleration;
        acceleration *= accelerationSign;
    }

    return acceleration;
}
float Vehicle::GetTurningAngle() {
    return GetMaxTurningAngle() * steeringWheelPosition;
}
float Vehicle::GetVelocity() {
    return velocity;
}
float Vehicle::GetSpeed() {
	return abs(velocity);
}
pair<float, float> Vehicle::GetPosition() {
    return position;
}
float Vehicle::GetFacingDirection() {
    return facingDirection;
}
void Vehicle::StartEngine() {
    engineRunning = true;
}
void Vehicle::StopEngine() {
    engineRunning = false;
}
void Vehicle::ShiftToReverse() {
    reverse = true;
}
void Vehicle::ShiftToDrive() {
	reverse = false;
}
void Vehicle::SetGasPedalPosition(float value) {
    if (value >= 0 && value <= 1)
        gasPedalPosition = value;
}
void Vehicle::SetBreakPedalPosition(float value) {
    if (value >= 0 && value <= 1)
        breakPedalPosition = value;
}
void Vehicle::SetSteeringWheelPosition(float value) {
    if (value >= -1 && value <= 1)
        steeringWheelPosition = value;
}
void Vehicle::SetFacingDirection(float value) {
    facingDirection = NormalizeAngle(value);
}
string Vehicle::GetAllInfo() {
    return "Speed: " + to_string(GetVelocity()) + ", Position: " + to_string(GetPosition().first) + ", " +
        to_string(GetPosition().second) + ", Facing Direction: " + to_string(GetFacingDirection()) + "(" +
        to_string(round(RadiansToDegrees(GetFacingDirection()))) + " deg)";
}

#pragma endregion

#pragma region Logging and Testing

void Vehicle::DoUpdateLogs() {
	if (logPositionEachUpdate)
		LogPosition();
}
void Vehicle::SetupLogs() {
    carGeneralLog = CreateOpenCarLog(CarGeneralLog, GetNameWithId());
    if (logPositionEachUpdate) {
        //Create a new log file for this car.
        positionLog = CreateOpenCarLog(CarPositionLog, GetNameWithId());
        Log(positionLog, "x1, y1");
    }
}
void Vehicle::CleanupLogs() {
    if (logPositionEachUpdate) {
        //Close the log file.
        CloseLog(positionLog);
    }
}
void Vehicle::LogPosition() {
    Log(positionLog, to_string(position.first) + "," + to_string(position.second));
}
void Vehicle::LogCarInfo(const string& text) {
    Log(carGeneralLog, text);
}
string Vehicle::GetNameWithId() {
    //return "TempCarName_" + to_string(id);
    //float weight = GetWeight();
    //string temp = GetName();
    //return "TempCarName_" + to_string(id);
    return GetName() + "_" + to_string(id);//This was causing the crash somehow.
}

#pragma endregion