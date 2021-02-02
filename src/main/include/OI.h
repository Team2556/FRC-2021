// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "RobotMap.h"
#include "frc/XboxController.h"
#include "frc/smartdashboard/SmartDashboard.h"

class OI {
 public:
  OI();

  bool bTestButton(int iButton);
  float fTestValue(int iControl);

  protected:
    frc::XboxController   Xbox1{XBOX_ONE};
    frc::XboxController   Xbox2{XBOX_TWO};
    frc::XboxController   Xbox3{XBOX_THREE};

};
