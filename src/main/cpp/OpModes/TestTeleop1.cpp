// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "OpModes/TestTeleop1.h"

TestTeleop1::TestTeleop1() 
{
    name = "test1";
    timesRun = 0;
}

void TestTeleop1::Start()
{
    timesRun++;
}

void TestTeleop1::Run()
{
    frc::SmartDashboard::PutNumber("Teleop 1 start times run", timesRun);
}

bool TestTeleop1::Complete()
{
    return false;
}
