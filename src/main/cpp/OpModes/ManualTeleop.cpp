// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "OpModes/ManualTeleop.h"

ManualTeleop::ManualTeleop() 
{
    name = "manual";
    timesRun = 0;
    interruptible = true;
}

void ManualTeleop::Start()
{
    timesRun++;
}

void ManualTeleop::Run()
{
    frc::SmartDashboard::PutNumber("Manual start times run", timesRun);
}

bool ManualTeleop::Complete()
{
    return false;
}