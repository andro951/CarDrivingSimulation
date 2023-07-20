#pragma once
#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include "CarManager.h"
#include "CarMath.h"

using namespace std;

class Vehicle {
    //Making GasVehicle and ElectricVehicle friends so that they can access the private members of Vehicle, while still keeping them private from
    //The derived classes of GasVehicle and ElectricVehicle.
    friend class GasVehicle;
    friend class ElectricVehicle;

public:
    Vehicle();
    Vehicle(const Vehicle& other);
    ~Vehicle();

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

    /// <summary>
    /// <para>The amount of stored energy in Whatt-hours.</para>
    /// <para>This is a calculated value from the amount of fuel or battery charge in the car.</para>
    /// </summary>
    float storedEnergy = 0;

    /// <summary>
    /// <para>The maximum amount of stored energy the car can hold in Whatt-hours.</para>
    /// <para>This is a calculated value from the maximum amount of fuel or battery capacity in the car.</para>
    /// </summary>
    float energyCapacity = 0;



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
    //Vehicle Model Properties
    virtual float GetGasTankCapacity() = 0;
    virtual float AccelerationStrength() = 0;
    virtual float BreakingStrength() = 0;
    virtual float GetMaxTurningAngle() = 0;
    virtual float GetAxleDistance() = 0;
    virtual float GetCarWindAndFrictionMultiplier() = 0;
    virtual float GetWeight() = 0;
    virtual string GetName() = 0;
    //Vehicle Model Properties

protected:
    void UpdateCarPositionAndFacingDirection(const float secondsSinceLastUpdate);
    void UpdateVelocity(const float secondsSinceLastUpdate, const float acceleration);
    void ConsumeStoredEnergy(const float secondsSinceLastUpdate, const float accelerationFromEngine);
    float& GetStoredEnergyRef();
    float GetStoredEnergy() const;
    float GetEnergyCapacity() const;

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
    bool CanAccelerate();
    float GetAcceleration(const float secondsSinceLastUpdate, float& accelerationFromEngine);
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