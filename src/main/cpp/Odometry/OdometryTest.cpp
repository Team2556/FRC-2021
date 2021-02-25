// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Odometry/OdometryTest.h"

OdometryTest::OdometryTest() 
{
    frc::SmartDashboard::PutString("test1", "pog");
    frc::SmartDashboard::PutString("test2", "pog");
    frc::SmartDashboard::PutString("test3", "pog");
    frc::SmartDashboard::PutString("test4", "pog");

    //will it get here??
}


float OdometryTest::getX()
{
    return Test.GetNumber("X", 0);
}

float OdometryTest::getY()
{
    return Test.GetNumber("Y", 0);
}

float OdometryTest::getYaw()
{
    return Test.GetNumber("Yaw", 0);
}
