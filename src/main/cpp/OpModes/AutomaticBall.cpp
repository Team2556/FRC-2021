// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "OpModes/AutomaticBall.h"

AutomaticBall::AutomaticBall()
{
    name = "autoBall";
    timesRun = 0;
}

void AutomaticBall::Start()
{
    timesRun++;
}

void AutomaticBall::Run()
{
    frc::SmartDashboard::PutNumber("autoBall start times run", timesRun);
}

bool AutomaticBall::Complete()
{
    return false;
}

//This opmode is probably going to be awful to write and not very useful outside of the autonomous period.