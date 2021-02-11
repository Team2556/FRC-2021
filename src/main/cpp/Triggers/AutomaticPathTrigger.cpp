// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Triggers/AutomaticPathTrigger.h"

AutomaticPathTrigger::AutomaticPathTrigger(OI * OIObjectParam)
{
    name = "autoTrench";
    DriverCMD = OIObjectParam;
}


bool AutomaticPathTrigger::Start()
{
    return DriverCMD->AutomaticPath();
}