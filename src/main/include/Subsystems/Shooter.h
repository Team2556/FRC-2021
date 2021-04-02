// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "math.h"

#include "Robot.h"
#include <ctre/Phoenix.h> //I think this is whats causing builds to take forever
#include "Utilities/Debug.h"

#define MAX_SHOOT_SPEED_ERROR 100 // since the shooter is spinning at about 11,000rpm, the error can be this high while still being close enough

class Shooter
{
public:
  Shooter(Robot *pRobot);

  // Wheel Functions
  bool SpinUp(); //uses encoder units per second spins up motor until reaches SetSpinSpeed (Running RPM)
  void SetSpinSpeed(double setSpinSpeed); //sets the target speed of motor (Desired RPM)
  void StopSpin();
  bool TargetSpeed(); //checks if motor is at target speed

  //Hood
  double SetHood(double setHoodAngle /*units is encoder ticks*/); //sets hood angle
  bool HoodAimed(); //checks angle of hood
  bool MoveHood(double setHoodSpeed); //Move hood to the angle SetHood has at given speed

  Robot *pRobot;

  // All of these values need to be set in the .cpp file
	double setShooterSpeedValue = pRobot->DriverCMD->shooterSpeedMult * maxEncoderSpeed; //need a function to set shooter speed; this is a placeholder for that
  int maxHoodAngle = -1200; //placeholder number for max hood angle
							              //(need to ask mechanical for real number)
	double setHoodValue = pRobot->DriverCMD->hoodAngleMult * maxHoodAngle; //setHoodAngle = 75% of max hood angle
                                                                        //need a function to set hood angle; this is a placeholder for that
  double setHoodSpeed; //need a function to set hood speed; this is a placeholder for that


  Debug ShooterDebug{"/Subsystems/Shooter"};

private:
  //CHECK ROBOT MAP (In Utilities) FOR MOTOR NAMES
  //Define two falcon 500s here. These will be the motors spinning the wheel that actually shoots the balls

  WPI_TalonFX Shooter_Motor_1{SHOOTER_MOTOR_1};
  WPI_TalonFX Shooter_Motor_2{SHOOTER_MOTOR_2};

  //Define a talon SRX here. This will move the hood

  WPI_TalonSRX Hood_Motor{HOOD_MOTOR};


  int maxEncoderSpeed = 2048;
	//Built-In Encoder Feedback: 2048 CPR Mag Encoder
};
