// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "OpModes/OpMode.h"

OpMode::OpMode()
{

}

//Begin OpMode
void OpMode::Start()
{
    frc::SmartDashboard::PutString("Overload Start", this->name);
}

//Called periodically to run OpMode. 
void OpMode::Run()
{
    frc::SmartDashboard::PutString("Overload Run", this->name);
}

//Returns true when OpMode finishes.
bool OpMode::Complete()
{
    frc::SmartDashboard::PutString("Overload Complete", this->name);
    return true;
}

