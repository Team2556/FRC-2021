// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "OpModes/AutomaticTrench.h"

AutomaticTrench::AutomaticTrench()
{
    name = "autoTrench";
    timesRun = 0;
}

void AutomaticTrench::Start()
{
    timesRun++;
}

void AutomaticTrench::Run()
{
    frc::SmartDashboard::PutNumber("autoTrench start times run", timesRun);
}

bool AutomaticTrench::Complete()
{
    return false;
}