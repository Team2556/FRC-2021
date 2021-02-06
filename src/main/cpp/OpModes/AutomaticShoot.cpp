// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "OpModes/AutomaticShoot.h"

AutomaticShoot::AutomaticShoot()
{
    name = "autoShoot";
    timesRun = 0;
}

void AutomaticShoot::Start()
{
    timesRun++;
}

void AutomaticShoot::Run()
{
    frc::SmartDashboard::PutNumber("AutoShoot start times run", timesRun);
}

bool AutomaticShoot::Complete()
{
    return false;
}