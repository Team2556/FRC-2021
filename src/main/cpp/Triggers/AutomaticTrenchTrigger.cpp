// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Triggers/AutomaticTrenchTrigger.h"

AutomaticTrenchTrigger::AutomaticTrenchTrigger(OI * OIObjectParam)
{
    name = "autoTrench";
    DriverCMD = OIObjectParam;
}


bool AutomaticTrenchTrigger::Start()
{
    return DriverCMD->AutomaticTrench();
}