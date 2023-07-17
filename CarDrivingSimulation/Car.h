#pragma once
#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include "CarManager.h"
#include "CarMath.h"

using namespace std;

class Car {
    //friend class Truck;

public:
    Car();
    Car(const Car& other);
    ~Car();

private:
    /// <summary>
    /// 
    /// </summary>
    pair<float, float> position = {0, 0};

    /// <summary>
    /// How fast the car is moving.  Can be negative if the car is moving backwards.
    /// </summary>
    float velocity = 0;

    /// <summary>
    /// <para>Value between 0 and 1.</para>
    /// <para>0 is no gas pedal pressed, 1 is gas pedal fully pressed</para>
    /// </summary>
    float gasPedalPosition = 0;

    /// <summary>
    /// <para>Value between 0 and 1.</para>
    /// <para>0 is no break pedal pressed, 1 is break pedal fully pressed</para>
    /// </summary>
    float breakPedalPosition = 0;

    /// <summary>
    /// <para>Value between -1 and 1.</para>
    /// <para>-1 is steering wheel fully left, 1 is steering wheel fully right</para>
    /// </summary>
    float steeringWheelPosition = 0;

    /// <summary>
    /// <para>Angle value between 0 and 2 pi radians</para>
    /// <para>Represents the angle of the car on the grid.  0 means facing right or East.</para>
    /// </summary>
    float facingDirection = 0;
    void SetFacingDirection(float value);

    bool engineRunning = false;
    bool reverse = false;

    /// <summary>
    /// Used to identify the car in the simulation.  No cars will have the same id.  The id corresponds to the index of the car in the
    /// CarDrivingSimulation's cars vector.
    /// </summary>
    int id = -1;



    const bool logPositionEachUpdate = true;

    /// <summary>
    /// Each car has its own log file.  carGeneralLog is for general info about the car.
    /// </summary>
    ofstream carGeneralLog;

    /// <summary>
    /// Each car will have its own log file.  Only used if logPositionEachUpdate is true.
    /// </summary>
    ofstream positionLog;

public:
    //Car Model Properties
    virtual float GetGasTankCapacity();
    virtual float AccelerationStrength();
    virtual float BreakingStrength();
    virtual float GetMaxTurningAngle();
    virtual float GetAxleDistance();
    virtual float GetCarWindAndFrictionMultiplier();
    virtual string GetName();
    //Car Model Properties

private:
    void UpdateCarPositionAndFacingDirection(const float secondsSinceLastUpdate);
    void UpdateSpeed(const float secondsSinceLastUpdate);

public:
    /// <summary>
    /// Perform 1 time actions at the beginning of the simulation.
    /// </summary>
    void Setup();

    /// <summary>
    /// Perform 1 time actions at the end of the simulation.
    /// </summary>
    void Cleanup();
    void Update(const float secondsSinceLastUpdate);
    float GetAcceleration(const float secondsSinceLastUpdate);
    float GetTurningAngle();
    float GetVelocity();

    /// <summary>
    /// Absolute value of velocity.
    /// </summary>
    float GetSpeed();
    pair<float, float> GetPosition();
    float GetFacingDirection();
    void StartEngine();
    void StopEngine();
    void ShiftToReverse();
    void ShiftToDrive();
    void SetGasPedalPosition(float value);
    void SetBreakPedalPosition(float value);
    void SetSteeringWheelPosition(float value);
    string GetAllInfo();

    void DoUpdateLogs();
    void SetupLogs();
    void CleanupLogs();
    void LogPosition();
    void LogCarInfo(const string& text);
    string GetNameWithId();
};