// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "OpModes/ManualTeleop.h"

ManualTeleop::ManualTeleop(Robot * pRobot, OI * DriverCMD, Climber * pClimber, ControlPanel * pCtrlPanel, Drivebase * pDrivebase, Feeder * pFeeder, Shooter * pShooter) 
{
    name = "manual";
    interruptible = true;
    this->pRobot = pRobot;
    this->DriverCMD = DriverCMD;
    this->pClimber = pClimber;
    this->pCtrlPanel = pCtrlPanel;
    this->pDrivebase = pDrivebase;
    this->pFeeder = pFeeder;
    this->pShooter = pShooter;
}

void ManualTeleop::Start()
{

}

void ManualTeleop::Run()
{
}

bool ManualTeleop::Complete()
{
    return false;
}
