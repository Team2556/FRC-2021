// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>
#include "OpModes/OpMode.h"
#include "OpModes/ManualTeleop.h"
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include "Utilities/OI.h"
#include "Triggers/Trigger.h"
#include "OpModes/OPController.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <ctre/Phoenix.h>
#include "Triggers/AutomaticPathTrigger.h"
#include "Triggers/AutomaticShootTrigger.h"
#include "Triggers/AutomaticBallTrigger.h"
#include "OpModes/AutomaticShoot.h"
#include "OpModes/AutomaticBall.h"
#include "frc/geometry/Pose2d.h"
#include "frc/DoubleSolenoid.h"
#include "Odometry/Jetson.h"
#include "Utilities/RobotMap.h"


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

//Motors

  WPI_TalonFX Shooter_Motor_1{SHOOTER_MOTOR_1};
  WPI_TalonFX Shooter_Motor_2{SHOOTER_MOTOR_2};

  WPI_TalonSRX Hood_Motor{HOOD_MOTOR};

//

  ManualTeleop * Manual;
  OI * DriverCMD;
  AutomaticBallTrigger * AutoBallTrigger;
  AutomaticShootTrigger * AutoShootTrigger;
  AutomaticBall * AutoBall;
  AutomaticShoot * AutoShoot;
  AutomaticPathTrigger * AutoPathTrigger;
  OPController * TeleopController;
  std::vector<Trigger*> TeleopTriggers;

  std::vector<frc::Pose2d*> testWaypoints;
  frc::Pose2d * pWaypoint1;
  frc::Pose2d * pWaypoint2;
  Jetson * JetsonController;

 private:
  
};
