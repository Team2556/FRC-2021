// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Subsystems/Shooter.h"

Shooter::Shooter(Robot *pRobot)
{
	this->pRobot = pRobot;
}


void Shooter::SetSpinSpeed(double setSpinSpeed)
{
	//double setSpinSpeed; //get desired speed from another function
	setShooterSpeedValue = setSpinSpeed;
	// This function should be just to set the speed for the spinup function so we souldn't call spinup here
	//SpinUp();
}


bool Shooter::SpinUp()
{
	ShooterDebug.PutNumber("Set Shoot Speed", setShooterSpeedValue);
	Shooter_Motor_1.Set(TalonFXControlMode::Velocity, setShooterSpeedValue);
	Shooter_Motor_2.Follow(Shooter_Motor_1);
	
	// the way you did this doesn't work because the the value from the encoder will never reach exactly the target value
	// bool spinUpReturn;
	// while (Shooter_Motor_1.GetSelectedSensorVelocity() != setShooterSpeedValue){
	// 	spinUpReturn = false;
	// }
	// if (Shooter_Motor_1.GetSelectedSensorVelocity() == setShooterSpeedValue)
	// {
	// 	frc::SmartDashboard::PutNumber("Shoot Speed", Shooter_Motor_1.GetSelectedSensorVelocity());
	// 	frc::SmartDashboard::PutNumber("Shoot Set Percent", Shooter_Motor_1.GetMotorOutputPercent());
	// 	spinUpReturn = true;
	// }
	ShooterDebug.PutNumber("Shooter Speed 1", Shooter_Motor_1.GetSelectedSensorVelocity());
	ShooterDebug.PutNumber("Shooter Speed 2", Shooter_Motor_2.GetSelectedSensorVelocity());
	ShooterDebug.PutNumber("Shooter Set Percent", Shooter_Motor_1.GetMotorOutputPercent());
	ShooterDebug.PutNumber("Motor 1 Current", pRobot->PDP.GetCurrent(SHOOTER_MOTOR_1_PDP));
	ShooterDebug.PutNumber("Motor 2 Current", pRobot->PDP.GetCurrent(SHOOTER_MOTOR_2_PDP));

	return TargetSpeed();
}

// Returns whether the shooter is within the error range of speed
bool Shooter::TargetSpeed(){
	// Shooter::SpinUp();
	// bool targetSpeedReturn;
	// if (Shooter::SpinUp()){
	// 	targetSpeedReturn = true;
	// }
	// else {
	// 	targetSpeedReturn = false;
	// }
	// frc::SmartDashboard::PutBoolean("At Target Speed", targetSpeedReturn);
	// return targetSpeedReturn;
	return fabs(setShooterSpeedValue - Shooter_Motor_1.GetSelectedSensorVelocity()) < MAX_SHOOT_SPEED_ERROR;
}


void Shooter::StopSpin()
{
	// This function is meant to just be a wrapper for SetSpeed(0)
	SetSpinSpeed(0);
	// frc::SmartDashboard::PutNumber("Set Output", 0);
	// Shooter_Motor_1.Set(TalonFXControlMode::PercentOutput, 0);
	// Shooter_Motor_2.Follow(Shooter_Motor_1);
	// frc::SmartDashboard::PutNumber("Shoot Speed", Shooter_Motor_1.GetSelectedSensorVelocity());
	// frc::SmartDashboard::PutNumber("Shoot Set Percent", Shooter_Motor_1.GetMotorOutputPercent());
}

double Shooter::SetHood(double setHood)
{
	//right now this function is a placeholder for the MoveHood fuction until i get some distance and angle values
	//it opens the hood 75% of max angle it can open
	frc::SmartDashboard::PutNumber("Set Angle", setHood);
	Hood_Motor.Set(TalonSRXControlMode::Position, setHood);
	frc::SmartDashboard::PutNumber("Hood Angle", Hood_Motor.GetSelectedSensorPosition());
	double setHoodAngle = setHood;
	return setHoodAngle;
}

bool Shooter::MoveHood(double setHoodSpeed){
	frc::SmartDashboard::PutNumber("Set Hood Speed", setHoodSpeed);
	frc::SmartDashboard::PutNumber("Set Hood Angle", Shooter::SetHood(setHoodValue));

	Hood_Motor.Set(TalonSRXControlMode::Velocity, setHoodSpeed);
	bool hoodAngleReturn;
	while (Hood_Motor.GetSelectedSensorPosition() != Shooter::SetHood(setHoodValue)){
		hoodAngleReturn = false;
	}
	if (Hood_Motor.GetSelectedSensorPosition() == Shooter::SetHood(setHoodValue))
	{
		frc::SmartDashboard::PutNumber("Hood Set Angle", Hood_Motor.GetSelectedSensorPosition());
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