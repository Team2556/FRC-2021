// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "OpModes/TestTeleop2.h"

TestTeleop2::TestTeleop2() 
{
    name = "test2";
    timesRun = 0;
}

void TestTeleop2::Start()
{
    timesRun++;
}

void TestTeleop2::Run()
{
    frc::SmartDashboard::PutNumber("Teleop 2 Start times run", timesRun);
}

bool TestTeleop2::Complete()
{
    return false;
}