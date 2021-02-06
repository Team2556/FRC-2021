// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>
#include "OpMode.h"
#include "OpModes/ManualTeleop.h"
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include "OI.h"
#include "Triggers/Trigger.h"
#include "OPController.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <ctre/Phoenix.h>
#include "Triggers/AutomaticTrenchTrigger.h"
#include "Triggers/AutomaticShootTrigger.h"
#include "Triggers/AutomaticBallTrigger.h"
#include "OpModes/AutomaticTrench.h"
#include "OpModes/AutomaticShoot.h"
#include "OpModes/AutomaticBall.h"

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

  ManualTeleop * Manual;
  OI * DriverCMD;
  AutomaticBallTrigger * AutoBallTrigger;
  AutomaticShootTrigger * AutoShootTrigger;
  AutomaticTrenchTrigger * AutoTrenchTrigger;
  AutomaticBall * AutoBall;
  AutomaticShoot * AutoShoot;
  AutomaticTrench * AutoTrench;
  OPController * TeleopController;

  std::vector<Trigger*> TeleopTriggers;

 private:
  
};
