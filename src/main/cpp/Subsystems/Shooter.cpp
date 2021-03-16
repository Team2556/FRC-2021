// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Subsystems/Shooter.h"
#include "math.h"

Shooter::Shooter(Robot *pRobot, Shooter *pShooter)
{
	this->pRobot = pRobot;
	this->pShooter = pShooter;
}


float Shooter::SetSpinSpeed(float setSpinSpeed)
{
	//float setSpinSpeed; //get desired speed from another function
	float setShooterSpeed = setSpinSpeed;
	Shooter::SpinUp();
	return setShooterSpeed;
}


bool Shooter::SpinUp()
{
	frc::SmartDashboard::PutNumber("Set Shoot Speed", setShooterSpeed);
	pShooter->Shooter_Motor_1.Set(TalonFXControlMode::Velocity, setShooterSpeed);
	pShooter->Shooter_Motor_2.Follow(pShooter->Shooter_Motor_1);
	bool spinUpReturn;
	while (float(pShooter->Shooter_Motor_1.GetSelectedSensorVelocity()) != setShooterSpeed){
		spinUpReturn = false;
	}
	if (float(pShooter->Shooter_Motor_1.GetSelectedSensorVelocity()) == setShooterSpeed)
	{
		frc::SmartDashboard::PutNumber("Shoot Speed", pShooter->Shooter_Motor_1.GetSelectedSensorVelocity());
		frc::SmartDashboard::PutNumber("Shoot Set Percent", pShooter->Shooter_Motor_1.GetMotorOutputPercent());
		spinUpReturn = true;
	}
	return spinUpReturn;
}


bool Shooter::TargetSpeed(){
	Shooter::SpinUp();
	bool targetSpeedReturn;
	if (Shooter::SpinUp()){
		frc::SmartDashboard::PutBoolean("At Target Speed", true);
		targetSpeedReturn = true;
	}
	else {
		frc::SmartDashboard::PutBoolean("At Target Speed", false);
		targetSpeedReturn = false;
	}
	return targetSpeedReturn;
}


void Shooter::StopSpin()
{

	frc::SmartDashboard::PutNumber("Set Output", 0);
	pShooter->Shooter_Motor_1.Set(TalonFXControlMode::PercentOutput, 0);
	pShooter->Shooter_Motor_2.Follow(pShooter->Shooter_Motor_1);
	frc::SmartDashboard::PutNumber("Shoot Speed", pShooter->Shooter_Motor_1.GetSelectedSensorVelocity());
	frc::SmartDashboard::PutNumber("Shoot Set Percent", pShooter->Shooter_Motor_1.GetMotorOutputPercent());
}

float Shooter::SetHood(float setHoodAngle)
{
	//right now this function is a placeholder for the MoveHood fuction until i get some distance and angle values
	//it opens the hood 75% of max angle it can open

	int maxHoodAngle = -1200; //placeholder number for max hood angle
							  //(need to ask mechanical for real number)
	setHoodAngle = pRobot->DriverCMD->hoodAngleMult * maxHoodAngle; //setHoodAngle = 75% of max hood angle
	frc::SmartDashboard::PutNumber("Set Angle", setHoodAngle);
	pShooter->Hood_Motor.Set(TalonSRXControlMode::Position, setHoodAngle);
	frc::SmartDashboard::PutNumber("Hood Angle", pShooter->Hood_Motor.GetSelectedSensorPosition());
	return setHoodAngle;
}

bool Shooter::MoveHood(float setHoodSpeed){

}

bool Shooter::HoodAimed(){
	float setHoodSpeed; //need a function to set hood speed; this is a placeholder for that
	Shooter::MoveHood(setHoodSpeed);
	bool hoodAimedReturn;
	if (Shooter::MoveHood(setHoodSpeed)){
	frc::SmartDashboard::PutBoolean("At Target Speed", true);
		hoodAimedReturn = true;
	}
	else {
		frc::SmartDashboard::PutBoolean("At Target Speed", false);
		hoodAimedReturn = false;
	}
	return hoodAimedReturn;

}