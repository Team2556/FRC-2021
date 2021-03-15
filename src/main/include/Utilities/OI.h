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
  
  float     fMoveForward();
  float     fMoveSideways();
  float     fRotate();
  bool      bManualRotate();
  bool      bResetGyro();
  int       POV();

  //Codriver Controls
  bool IntakeExtension(); //Extend the intake system
  float IntakeRun(); //Run intake
  float HopperRun(); //Spin hopper
  float HopperKickup(); //Kickup balls in hopper
  bool StopShoot();
  //Feeder

  // Test Functions
  bool bTestButton(int iButton);
  float fTestValue(int iControl);


  float shooterSpeedMult = .9;
  float hoodAngleMult = .75; 

  protected:
    frc::XboxController   Xbox1{XBOX_ONE};
    frc::XboxController   Xbox2{XBOX_TWO}; //CoDriver 
    frc::XboxController   Xbox3{XBOX_THREE};
  

    Debug OIDebug{"/Subsystems/OI"};

};
