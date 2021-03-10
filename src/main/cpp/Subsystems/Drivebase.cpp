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
    //normalize to [-180, 180]
    rotate = fmod((rotate + 3600.0), 360);
    if(rotate > 180)
    {
        rotate -= 360;
    }
    MecanumDrive.DrivePolar(speed, direction, rotate);
}

void Drivebase::Drive(float fForward, float fStrafe, float rotate, float gyro)
{
    MecanumDrive.DriveCartesian(fStrafe, fForward, rotate, gyro);
}