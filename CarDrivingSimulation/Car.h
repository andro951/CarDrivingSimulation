#pragma once
#include <utility>

const float PI = 3.14159265358979323846f;

class Car {
private:
    std::pair<float, float> position = {0, 0};
    float speed = 0;

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
    /// <para>Angle value between 0 and 2? radians</para>
    /// <para>Represents the angle of the car on the grid.  0 means facing right or East.</para>
    /// </summary>
    float facingDirection = 0;
    bool engineRunning = false;
    bool reverse = false;

public:
    //Car Model Properties
    virtual float GetGasTankCapacity();
    virtual float AccelerationStrength();
    virtual float BreakingStrength();
    virtual float GetMaxTurningAngle();
    virtual float GetAxleDistance();
    //Car Model Properties

private:
    void UpdateCarPositionAndFacingDirection(const float secondsSinceLastUpdate);
    void UpdateSpeed(const float secondsSinceLastUpdate);

public:
    void Update(const float secondsSinceLastUpdate);
    float GetAcceleration(const float secondsSinceLastUpdate);
    float GetTurningAngle();
    float GetSpeed();
    std::pair<float, float> GetPosition();
    float GetFacingDirection();
    void StartEngine();
    void StopEngine();
    void ShiftToReverse();
    void ShiftToDrive();
    void SetGasPedalPosition(float value);
    void SetBreakPedalPosition(float value);
    void SetSteeringWheelPosition(float value);
};