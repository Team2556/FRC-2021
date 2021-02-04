// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Triggers/TestTrigger2.h"

TestTrigger2::TestTrigger2(OI * OIObjectParam) 
{
    name = "test2";
    DriverCMD = OIObjectParam;
}

bool TestTrigger2::Start()
{
    //frc::SmartDashboard::PutString("In Trigger 2", "yes");
    return DriverCMD->TestTeleop2();
}