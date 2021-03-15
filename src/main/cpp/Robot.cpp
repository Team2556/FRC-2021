// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>
#include "OpModes/AutomaticPath.h"
#include "Odometry/Odometry.h"
#include <thread>
#include "Subsystems/Drivebase.h"
#include "Subsystems/Shooter.h"
#include "Subsystems/Feeder.h"
#include "Subsystems/ControlPanel.h"
#include "Subsystems/Climber.h"

#include "OpModes/ManualTeleop.h"
#include "OpModes/AutomaticShoot.h"
#include "OpModes/AutomaticBall.h"
#include "Triggers/AutomaticPathTrigger.h"
#include "Triggers/AutomaticShootTrigger.h"
#include "Triggers/AutomaticBallTrigger.h"

AutomaticPath * AutoPath;
Drivebase * MecanumDrive;
Odometry * OdometryController;
Shooter * ShooterController;
Climber * ClimberController;
ControlPanel * CtrlPanel;
Feeder * FeederController;
ManualTeleop * Manual;
AutomaticBall * AutoBall;
AutomaticShoot * AutoShoot;
AutomaticBallTrigger * AutoBallTrigger;
AutomaticShootTrigger * AutoShootTrigger;
AutomaticPathTrigger * AutoPathTrigger;
OPController * TeleopController;

void Robot::RobotInit() 
{
  pWaypoint1 = new frc::Pose2d{10_m, 10_m, frc::Rotation2d(0_deg)};
  pWaypoint2 = new frc::Pose2d{20_m, 10_m, frc::Rotation2d(0_deg)};
  testWaypoints.push_back(pWaypoint1);
  testWaypoints.push_back(pWaypoint2);

  MecanumDrive = new Drivebase(this);
  OdometryController = new Odometry(MecanumDrive);
  // JetsonController = new Jetson();
  AutoPath = new AutomaticPath(this, testWaypoints, MecanumDrive, OdometryController);
  AutoBall = new AutomaticBall();
  AutoShoot = new AutomaticShoot();
  Manual =  new ManualTeleop(this, ClimberController, CtrlPanel, MecanumDrive, FeederController, ShooterController);
  DriverCMD = new OI();
  AutoShootTrigger = new AutomaticShootTrigger(DriverCMD);
  AutoPathTrigger = new AutomaticPathTrigger(DriverCMD);
  AutoBallTrigger = new AutomaticBallTrigger(DriverCMD);
  

  TeleopModes.push_back(AutoPath);
  TeleopModes.push_back(AutoBall);
  TeleopModes.push_back(AutoShoot);
  TeleopModes.push_back(Manual);
  TeleopTriggers.push_back(AutoShootTrigger);
  TeleopTriggers.push_back(AutoBallTrigger);
  TeleopTriggers.push_back(AutoPathTrigger);


  TeleopController = new OPController(DriverCMD, TeleopModes, TeleopTriggers);
}


void Robot::RobotPeriodic() 
{

}


void Robot::AutonomousInit() 
{

}

void Robot::AutonomousPeriodic() 
{
  
}

void Robot::TeleopInit() 
{
  // std::string name = TeleopController->nextOp()->name;
  // frc::SmartDashboard::PutString("Next Op", name);
  // frc::SmartDashboard::PutBoolean("manual", Manual->interruptible);
  // frc::SmartDashboard::PutBoolean("test1", Teleop1->interruptible);
}

void Robot::TeleopPeriodic() 
{
  //printf("address is %p and address 2 is %p\n", (void *)TeleopModes[0], *((int *)(void * )TeleopController->nextOp()));
  //TeleopController->nextOp();
  //TeleopController->test();
  //frc::SmartDashboard::PutBoolean("button", DriverCMD->bTestButton(0));
  //frc::SmartDashboard::PutString("Next Op", TeleopController->nextOp()->name);
  TeleopController->ControllerPeriodic();
  frc::SmartDashboard::PutString("Current OpMode", TeleopController->CurrOp->name);
  frc::SmartDashboard::PutNumber("EncoderSpeed", OdometryController->testGetEncoder());
  MecanumDrive->Drive(DriverCMD->fMoveForward(), DriverCMD->fMoveSideways(), DriverCMD->fRotate(), 0);
}

void Robot::DisabledInit() 
{
  //OdometryController->OdometryPeriodicThread.~thread();
  //JetsonController->JetsonReceiverThread.~thread();
}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
