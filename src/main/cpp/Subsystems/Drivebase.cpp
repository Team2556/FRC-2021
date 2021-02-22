// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Subsystems/Drivebase.h"

Drivebase::Drivebase(Robot * pRobot)
{
    this->pRobot = pRobot;
}

//Drives the robot using a speed, direction, and rotation. 
void Drivebase::PolarDrive(float speed, float direction, float rotate, float gyro)
{
    return;
}
