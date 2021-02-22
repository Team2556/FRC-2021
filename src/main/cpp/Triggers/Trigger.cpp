// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Triggers/Trigger.h"

Trigger::Trigger() 
{
    name = "manual";
}

//Check whether conditions are met to start an opmode. 
bool Trigger::Start()
{
    frc::SmartDashboard::PutString("override", "overide default start");
    return false;
}
