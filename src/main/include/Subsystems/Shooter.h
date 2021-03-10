// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "Utilities/Debug.h"
#include "Robot.h"
#include "Feeder.h"

class Shooter
{
public:
  Shooter(Robot *pRobot, Shooter *pShooter);

  // Wheel Functions
  bool SpinUp(); //uses encoder units per second spins up motor until reaches SetSpinSpeed (Running RPM)
  float SetSpinSpeed(); //sets the target speed of motor (Desired RPM)
  void StopSpin();
  bool TargetSpeed(); //checks if motor is at target speed

  //Hood
  float SetHood(float setHoodAngle /*units is encoder ticks*/); //sets hood angle
  bool HoodAimed(); //checks angle of hood
  void MoveHood(float setHoodSpeed); //Move hood to the angle SetHood has at given speed

  Robot *pRobot;
  Feeder *pFeeder;
  Shooter *pShooter;

  Debug ShooterDebug{"/Subsystems/Shooter"};

private:
  //CHECK ROBOT MAP (In Utilities) FOR MOTOR NAMES
  //Define two falcon 500s here. These will be the motors spinning the wheel that actually shoots the balls

  WPI_TalonFX Shooter_Motor_1{SHOOTER_MOTOR_1};
  WPI_TalonFX Shooter_Motor_2{SHOOTER_MOTOR_2};

  //Define a talon SRX here. This will move the hood

  WPI_TalonSRX Hood_Motor{HOOD_MOTOR};
};
