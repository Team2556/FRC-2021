// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Subsystems/Shooter.h"

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
	frc::SmartDashboard::PutNumber("Set Shoot Speed", setShooterSpeedValue);
	pShooter->Shooter_Motor_1.Set(TalonFXControlMode::Velocity, setShooterSpeedValue);
	pShooter->Shooter_Motor_2.Follow(pShooter->Shooter_Motor_1);
	bool spinUpReturn;
	while (pShooter->Shooter_Motor_1.GetSelectedSensorVelocity() != setShooterSpeedValue){
		spinUpReturn = false;
	}
	if (pShooter->Shooter_Motor_1.GetSelectedSensorVelocity() == setShooterSpeedValue)
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
		targetSpeedReturn = true;
	}
	else {
		targetSpeedReturn = false;
	}
	frc::SmartDashboard::PutBoolean("At Target Speed", targetSpeedReturn);
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

float Shooter::SetHood(float setHood)
{
	//right now this function is a placeholder for the MoveHood fuction until i get some distance and angle values
	//it opens the hood 75% of max angle it can open
	frc::SmartDashboard::PutNumber("Set Angle", setHood);
	pShooter->Hood_Motor.Set(TalonSRXControlMode::Position, setHood);
	frc::SmartDashboard::PutNumber("Hood Angle", pShooter->Hood_Motor.GetSelectedSensorPosition());
	float setHoodAngle = setHood;
	return setHoodAngle;
}

bool Shooter::MoveHood(float setHoodSpeed){
	frc::SmartDashboard::PutNumber("Set Hood Speed", setHoodSpeed);
	frc::SmartDashboard::PutNumber("Set Hood Angle", Shooter::SetHood(setHoodValue));

	pShooter->Hood_Motor.Set(TalonSRXControlMode::Velocity, setHoodSpeed);
	bool hoodAngleReturn;
	while (pShooter->Hood_Motor.GetSelectedSensorPosition() != Shooter::SetHood(setHoodValue)){
		hoodAngleReturn = false;
	}
	if (pShooter->Hood_Motor.GetSelectedSensorPosition() == Shooter::SetHood(setHoodValue))
	{
		frc::SmartDashboard::PutNumber("Hood Set Angle", pShooter->Hood_Motor.GetSelectedSensorPosition());
		hoodAngleReturn = true;
	}
	return hoodAngleReturn;
}

bool Shooter::HoodAimed(){
	
	bool hoodAimedReturn;
	if (Shooter::MoveHood(setHoodSpeed)){
		hoodAimedReturn = true;
	}
	else {
		hoodAimedReturn = false;
	}
	frc::SmartDashboard::PutBoolean("At Target Angle", hoodAimedReturn);
	return hoodAimedReturn;

}