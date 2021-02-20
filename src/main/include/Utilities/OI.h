// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "RobotMap.h"
#include "frc/XboxController.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include "Utilities/Debug.h"

class OI {
 public:
  OI();

  //OPMode Controls
  bool CancelOP(); // Cancel the current op
  bool AutomaticShoot(); //Start shooting
  bool AutomaticBall(); //Start picking up balls
  bool AutomaticPath(); //Start Trench
  //Driving Controls
  double xSpeed(); //Measures the x movement of the left joystick
  double ySpeed(); //Measures the y movement of the left joystick
  double rotate(); //Measures the x movement of the right joystick
  bool allowRotate(); //Whether the driver can manually rotate the robot or not
  //Codriver Controls
  bool IntakeExtension(); //Extend the intake system
  float IntakeRun(); //Run intake
  float HopperRun(); //Spin hopper
  float HopperKickup(); //Kickup balls in hopper

  //Feeder
    float speedMult = .9;

  // Test Functions
  bool bTestButton(int iButton);
  float fTestValue(int iControl);

  protected:
    frc::XboxController   Xbox1{XBOX_ONE};
    frc::XboxController   Xbox2{XBOX_TWO};
    frc::XboxController   Xbox3{XBOX_THREE};
  

    Debug OIDebug{"/Subsystems/OI"};

};
