// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Subsystems/Shooter.h"

Shooter::Shooter(Robot *pRobot)
{
	this->pRobot = pRobot;
}

//Wheel (Shooter) Functions

void Shooter::SetSpinSpeed(double setSpinSpeed)
{
	//This function should be just to set the speed for the spinup function
	if (setSpinSpeed > MAX_ENCODER_SPEED) //makes sure given speed wont exceed max encoder speed and break the motor
	{
		setShooterSpeedValue = MAX_ENCODER_SPEED; //set shooter speed to max encoder speed
	}
	else //in this case given speed is less than max encoder speed
	{
		setShooterSpeedValue = setSpinSpeed; //sets shooter speed to given speed
	}
}

bool Shooter::TargetSpeed()
{
	//returns true if the shooter speed error (difference between target speed and actual speed)
	//is less than max allowed error (because the encoder will never reach exactly the target value)
	//else returns false
	return (fabs(setShooterSpeedValue - Shooter_Motor_1.GetSelectedSensorVelocity()) < MAX_SHOOT_SPEED_ERROR);
}

bool Shooter::SpinUp()
{
	//Sets Motors
	ShooterDebug.PutNumber("Set Shoot Speed", setShooterSpeedValue);		 //puts value of shooter speed target to ShooterDebug
	Shooter_Motor_1.Set(TalonFXControlMode::Velocity, setShooterSpeedValue); //sets shooter to target speed
	Shooter_Motor_2.Follow(Shooter_Motor_1);								 //sets motor 2 to the same value as motor 1

	//Temperature Control
	//checks temperature of motors and pushes cold air into them if they are too hot
	if (Shooter_Motor_1.GetTemperature() > MAX_TEMPERATURE) //checks temperature of motor 1 and pushes cold air into them if they are too hot
	{
		Shooter_Solenoid.Set(frc::DoubleSolenoid::kForward); //pushes cold air into motors to cool them down
	}
	else if (Shooter_Motor_2.GetTemperature() > MAX_TEMPERATURE) //checks temperature of motor 2
	{
		Shooter_Solenoid.Set(frc::DoubleSolenoid::kForward); //pushes cold air into motors to cool them down
	}
	else //in this case motor tempurature is fine so they dont need cool air
	{
		Shooter_Solenoid.Set(frc::DoubleSolenoid::kReverse); //pushes cold air away from motors
	}

	//ShooterDebug
	//puts value of shooter speed, motor percentage, temperature, and motor current to ShooterDebug
	ShooterDebug.PutNumber("Shooter Speed 1", Shooter_Motor_1.GetSelectedSensorVelocity());
	ShooterDebug.PutNumber("Shooter Speed 2", Shooter_Motor_2.GetSelectedSensorVelocity());

	ShooterDebug.PutNumber("Shooter Set Percent 1", Shooter_Motor_1.GetMotorOutputPercent());
	ShooterDebug.PutNumber("Shooter Set Percent 2", Shooter_Motor_2.GetMotorOutputPercent());

	ShooterDebug.PutNumber("Motor 1 Temperature", Shooter_Motor_1.GetTemperature());
	ShooterDebug.PutNumber("Motor 2 Temperature", Shooter_Motor_2.GetTemperature());

	ShooterDebug.PutNumber("Motor 1 Current", pRobot->PDP.GetCurrent(SHOOTER_MOTOR_1_PDP));
	ShooterDebug.PutNumber("Motor 2 Current", pRobot->PDP.GetCurrent(SHOOTER_MOTOR_2_PDP));

	//Margin of Error
	return TargetSpeed(); //returns true if shooter is at intended speed (within givin margin of error)
}

void Shooter::StopSpin()
{
	SetSpinSpeed(0); //sets speed of shooter motors to zero (stops the shooter motors)
}

//Hood

void Shooter::SetHood(double setHood)
{
	if (setHood > MAX_HOOD_ANGLE) //makes sure given hood angle wont exceed max hood hangle and break it
	{
		setHoodValue = MAX_HOOD_ANGLE; //set hood angle to max angle
	}

	else if (setHood < MIN_HOOD_ANGLE) //makes sure given hood angle wont exceed min hood hangle and break it
	{
		setHoodValue = MIN_HOOD_ANGLE; //set hood angle to min angle
	}

	else
	{
		setHoodValue = setHood; //sets hood angle to given hood angle if it is between max and min hood angles
	}
}

bool Shooter::HoodAimed()
{
	return (fabs(setHoodValue - Hood_Motor.GetSelectedSensorPosition()) < MAX_HOOD_ANGLE_ERROR);
	//returns true if the hood angle error (difference between target angle and actual angle) is less than max allowed error; else returns false
}

bool Shooter::MoveHood()
{

	ShooterDebug.PutNumber("Set Hood Angle", setHoodValue); //puts target angle in ShooterDebug

	Hood_Motor.Set(TalonSRXControlMode::Position, setHoodValue); //set hood to target angle

	//puts value of hood angle, motor percentage, and the calculated error of hood to ShooterDebug
	ShooterDebug.PutNumber("Hood Angle Value", Hood_Motor.GetSelectedSensorPosition());
	ShooterDebug.PutNumber("Hood Set Percent", Hood_Motor.GetMotorOutputPercent());
	ShooterDebug.PutNumber("Hood Error", (setHoodValue - Hood_Motor.GetSelectedSensorPosition()));

	return HoodAimed(); //returns true if hood is at intended angle (within given margin of error)
}

//Manual Functions

bool Shooter::ManualShoot(double manualSetSpinSpeed)
{
	//sets the speed to any input (such as pulled from a joystick) for testing purposes and the like
	Shooter_Motor_1.Set(TalonFXControlMode::Velocity, manualSetSpinSpeed);
	Shooter_Motor_2.Follow(Shooter_Motor_1);

	return TargetSpeed();
}

bool Shooter::ManualHood(double manualHoodAngle)
{
	//sets the hood angle to any input (such as pulled from a joystick) for testing purposes and the like
	Hood_Motor.Set(TalonSRXControlMode::Position, manualHoodAngle);

	return HoodAimed();
}