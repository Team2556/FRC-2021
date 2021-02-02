// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Triggers/TestTrigger1.h"

TestTrigger1::TestTrigger1(OI * OIObjectParam)
{
    name = "test1";
    OIObject = OIObjectParam;
}


bool TestTrigger1::Start()
{
    return OIObject->bTestButton(0);
}