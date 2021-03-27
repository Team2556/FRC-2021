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

double fNormalizeAngle360(double fAngle);
double fNormalizeAngle180(double fAngle);

void NavGyro::Update()
{
    PrevYaw = CurrentYaw;
    CurrentYaw = pNavX->GetYaw();
    Speed = PrevYaw - CurrentYaw;;
}

//Returns the degree value of the robot's counterclockwise angle from vertical heading
double NavGyro::getYaw()
{
    return CurrentYaw;
    // return pNavX->GetYaw();
}

double NavGyro::getYawSpeed()
{
    return Speed;
    // return pNavX->GetRate();
}

// Get the current command yaw
double NavGyro::getCommandYaw()
{
    return CommandYaw;
}

// Set a new command yaw
void NavGyro::setCommandYaw(double yaw)
{
    CommandYaw = yaw;
}

double NavGyro::GetYawError()
{
    double value = fNormalizeAngle180(CommandYaw - getYaw());
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

double fNormalizeAngle360(double fAngle)
{
    while (fAngle <    0.0) fAngle += 360.0;
    while (fAngle >= 360.0) fAngle -= 360.0;
    return fAngle;
}


// ----------------------------------------------------------------------------

// Normalize fAngle range from +180.0 to -180.0

double fNormalizeAngle180(double fAngle)
{
    while (fAngle <  -180.0) fAngle += 360.0;
    while (fAngle >=  180.0) fAngle -= 360.0;
    return fAngle;
}