// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "math.h"

#include "Robot.h"
#include <ctre/Phoenix.h> //I think this is whats causing builds to take forever
#include "Utilities/Debug.h"

class Shooter
{
public:
  Shooter(Robot *pRobot);

  //Wheel (Shooter) Functions
  void SetSpinSpeed(double setSpinSpeed); //sets the target speed of motor (Desired RPM)
  bool TargetSpeed();                     //checks if motor is at target speed
  bool SpinUp();                          //runs motor to SetSpinSpeed (Running RPM)
  void StopSpin();                        //stops shooter motors

  //Hood Functions
  void SetHood(double setHoodAngle); //sets hood angle target
  bool HoodAimed();                  //checks angle of hood
  bool MoveHood();                   //Move hood to the angle SetHood has

  //Manual Functions
  //these set the speed and hood angle to any input (such as pulled from a joystick) for testing purposes and the like
  bool ManualShoot(double manualSetSpinSpeed);
  bool ManualHood(double manualHoodAngle);

  Robot *pRobot;

  //Variables

  //All of these values need to be set in the .cpp file
  double setShooterSpeedValue;
  double setHoodValue;

  //can define these in drivebase or something, possibly connect them to a joystick
  double manualSetSpinSpeed;
  double manualHoodAngle;

  //Other
  Debug ShooterDebug{"/Subsystems/Shooter"};

private:
  //Shooter Motors
  WPI_TalonFX Shooter_Motor_1{SHOOTER_MOTOR_1};
  WPI_TalonFX Shooter_Motor_2{SHOOTER_MOTOR_2};

  //Hood Motor
  WPI_TalonSRX Hood_Motor{HOOD_MOTOR};

  //Solenoid
  frc::DoubleSolenoid Shooter_Solenoid{CAN_PCM_SHOOTER, SHOOTER_OUT, SHOOTER_IN};

  //Error Values
#define MAX_SHOOT_SPEED_ERROR 100 //since the shooter is spinning at about 11,000rpm, the error can be this high while still being close enough
#define MAX_HOOD_ANGLE_ERROR 5

  //Max and Min Values
#define MAX_TEMPERATURE 50 //in Celcius
#define MAX_ENCODER_SPEED 2048
#define MAX_HOOD_ANGLE 1200
#define MIN_HOOD_ANGLE 0
};
