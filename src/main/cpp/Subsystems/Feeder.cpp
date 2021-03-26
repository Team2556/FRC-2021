// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

//Similar intake to sandman. Two motors for hopper (middle and kickup)
#include "Subsystems/Feeder.h"

Feeder::Feeder()
{

}


void Feeder::KickUp(float Speed)
{
    Hopper_Kickup.Set(Speed);
}

void Feeder::SpinHopper(float speed)
{
    Hopper_Spinner.Set(-1 * fabs(speed));
}

void Feeder::SetIntake(bool Extended)
{
    if (Extended == true)
    {
    Intake_Solenoid.Set(frc::DoubleSolenoid::Value::kForward);
    }
    else
    {
    Intake_Solenoid.Set(frc::DoubleSolenoid::Value::kReverse);    
    }
}

void Feeder::RunIntake(float speed)
{
    Intake_Motor.Set(speed);
}