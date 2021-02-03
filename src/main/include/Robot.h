// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>
#include "OpMode.h"
#include "OpModes/TestTeleop1.h"
#include "OpModes/TestTeleop2.h"
#include "OpModes/ManualTeleop.h"
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include "OI.h"
#include "Triggers/Trigger.h"
#include "Triggers/TestTrigger1.h"
#include "Triggers/TestTrigger2.h"
#include "OPController.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <ctre/Phoenix.h>

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;

  std::vector<OpMode*> AutoModes;
  std::vector<OpMode*> TeleopModes;

  TestTeleop1 * Teleop1;
  TestTeleop2 * Teleop2;
  ManualTeleop * Manual;
  OI * DriverCMD;
  TestTrigger1 * TeleopTrigger1;
  TestTrigger2 * TeleopTrigger2;
  OPController * TeleopController;

  std::vector<Trigger*> TeleopTriggers;

 private:
  
};
