// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Subsystems/Shooter.h"
#include "math.h"

Shooter::Shooter(Robot * pRobot, Feeder * pFeeder){
    this->pRobot = pRobot;
	this->pFeeder = pFeeder;
}

bool Shooter::SpinUp(){
	float speed = -pRobot->DriverCMD->speedMult *33700; //max 33700 encoder 4930 rpm
	frc::SmartDashboard::PutNumber("Set Speed", speed);
	pRobot->Shooter_Motor_1.Set(ControlMode::Velocity, speed);
	pRobot->Shooter_Motor_2.Follow(pRobot->Shooter_Motor_1);
	frc::SmartDashboard::PutNumber("Shoot Speed", pRobot->Shooter_Motor_1.GetSelectedSensorVelocity());
	frc::SmartDashboard::PutNumber("Shoot Set Percent", pRobot->Shooter_Motor_1.GetMotorOutputPercent());
}