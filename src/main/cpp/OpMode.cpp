// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "OpMode.h"

OpMode::OpMode()
{

}


void OpMode::Start()
{
    frc::SmartDashboard::PutString("Overload Start", this->name);
}

void OpMode::Run()
{
    frc::SmartDashboard::PutString("Overload Run", this->name);
}

bool OpMode::Complete()
{
    frc::SmartDashboard::PutString("Overload Complete", this->name);
    return true;
}

