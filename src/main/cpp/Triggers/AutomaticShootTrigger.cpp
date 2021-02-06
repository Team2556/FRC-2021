// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Triggers/AutomaticShootTrigger.h"

AutomaticShootTrigger::AutomaticShootTrigger(OI * OIObjectParam)
{
    name = "autoShoot";
    DriverCMD = OIObjectParam;
}


bool AutomaticShootTrigger::Start()
{
    return DriverCMD->AutomaticShoot();
}