// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Odometry/NavGyro.h"

NavGyro::NavGyro()
{
    pNavX = new AHRS(frc::SPI::Port::kMXP);
    pNavX->Reset();
    this->CommandYaw = pNavX->GetYaw();
    PrevYaw = pNavX->GetYaw();
}

float fNormalizeAngle360(float fAngle);
float fNormalizeAngle180(float fAngle);

void NavGyro::Update()
{
    PrevYaw = CurrentYaw;
    CurrentYaw = pNavX->GetYaw();
    Speed = PrevYaw - CurrentYaw;;
}

//Returns the degree value of the robot's counterclockwise angle from vertical heading
float NavGyro::getYaw()
{
    return CurrentYaw;
    // return pNavX->GetYaw();
}

float NavGyro::getYawSpeed()
{
    return Speed;
    // return pNavX->GetRate();
}

// Get the current command yaw
float NavGyro::getCommandYaw()
{
    return CommandYaw;
}

// Set a new command yaw
void NavGyro::setCommandYaw(float yaw)
{
    CommandYaw = yaw;
}

float NavGyro::GetYawError()
{
    float value = fNormalizeAngle180(CommandYaw - getYaw());
    NavXDebug.PutNumber("Yaw Error", value);
    return value;
}

void NavGyro::ResetYaw()
{
    pNavX->Reset();
    Update();
    CommandYaw = getYaw();
}

// ----------------------------------------------------------------------------
// Utilities
// ----------------------------------------------------------------------------

// Normalize fAngle range from 0.0 to 360.0

float fNormalizeAngle360(float fAngle)
{
    while (fAngle <    0.0) fAngle += 360.0;
    while (fAngle >= 360.0) fAngle -= 360.0;
    return fAngle;
}


// ----------------------------------------------------------------------------

// Normalize fAngle range from +180.0 to -180.0

float fNormalizeAngle180(float fAngle)
{
    while (fAngle <  -180.0) fAngle += 360.0;
    while (fAngle >=  180.0) fAngle -= 360.0;
    return fAngle;
}