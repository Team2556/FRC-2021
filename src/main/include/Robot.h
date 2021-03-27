// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>
#include <iostream>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include "frc/smartdashboard/SmartDashboard.h"
#include <ctre/Phoenix.h>
#include "frc/geometry/Pose2d.h"
#include "frc/DoubleSolenoid.h"

#include "Triggers/Trigger.h"
#include "OpModes/OpMode.h"
#include "OpModes/OPController.h"

#include "Odometry/NavGyro.h"
#include <Odometry/Limelight.h>

#include "Utilities/RobotMap.h"
#include "Utilities/OI.h"

class Robot : public frc::TimedRobot
{
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

  std::vector<OpMode *> AutoModes;
  std::vector<OpMode *> TeleopModes;
  OPController *TeleopController;
  std::vector<Trigger *> TeleopTriggers;

  // NavX
  NavGyro Nav;
  Limelight limelight;

  //ManualTeleop *Manual;
  OI * DriverCMD;


  std::vector<frc::Pose2d *> testWaypoints;
  frc::Pose2d *pWaypoint1;
  frc::Pose2d *pWaypoint2;

private:
};
