// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "OpModes/ManualTeleop.h"

ManualTeleop::ManualTeleop(Robot * pRobot, Climber * pClimber, ControlPanel * pCtrlPanel, Drivebase * pDrivebase, Feeder * pFeeder, Shooter * pShooter) 
{
    name = "manual";
    timesRun = 0;
    interruptible = true;
    this->pRobot = pRobot;
    this->pClimber = pClimber;
    this->pCtrlPanel = pCtrlPanel;
    this->pDrivebase = pDrivebase;
    this->pFeeder = pFeeder;
    this->pShooter = pShooter;
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