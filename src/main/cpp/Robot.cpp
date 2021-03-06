// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.



#include "Robot.h"

//Subsystem includes
#include "Subsystems/Drivebase.h"
//#include "Subsystems/Shooter.h"
//#include "Subsystems/Feeder.h"
#include "Subsystems/ControlPanel.h"
#include "Subsystems/Climber.h"


#include "OpModes/ManualTeleop.h"
#include "OpModes/AutomaticPath.h"
#include "OpModes/AutomaticShoot.h"
#include "OpModes/AutomaticBall.h"

#include "Triggers/AutomaticPathTrigger.h"
#include "Triggers/AutomaticShootTrigger.h"
#include "Triggers/AutomaticBallTrigger.h"

//Subsystems
Drivebase * MecanumDrive;
Shooter * ShooterController;
Climber * ClimberController;
ControlPanel * CtrlPanel;
Feeder * FeederController;

Odometry * OdometryController;

// OpModes
AutomaticPath * AutoPathTest;
ManualTeleop * Manual;
AutomaticBall * AutoBall;
AutomaticShoot * AutoShoot;

// Triggers
AutomaticBallTrigger * AutoBallTrigger;
AutomaticShootTrigger * AutoShootTrigger;
AutomaticPathTrigger * AutoPathTestTrigger;

void Robot::RobotInit() 
{
  pWaypoint1 = new frc::Pose2d{10_m, 10_m, frc::Rotation2d(0_deg)};
  pWaypoint2 = new frc::Pose2d{20_m, 10_m, frc::Rotation2d(0_deg)};
  testWaypoints.push_back(pWaypoint1);
  testWaypoints.push_back(pWaypoint2);

  
  //OdometryTester = new OdometryTest();
  //JetsonController = new Jetson();
  //The Drivebase is the issue. #cringe
  MecanumDrive = new Drivebase(this);
  FeederController = new Feeder();
  OdometryController = new Odometry(this, MecanumDrive);
  AutoPathTest = new AutomaticPath(this, testWaypoints, MecanumDrive, OdometryController);
  AutoBall = new AutomaticBall();
  AutoShoot = new AutomaticShoot();
  DriverCMD = new OI();
  Manual =  new ManualTeleop(this, DriverCMD, ClimberController, CtrlPanel, MecanumDrive, FeederController, ShooterController);
  AutoShootTrigger = new AutomaticShootTrigger(DriverCMD);
  AutoPathTestTrigger = new AutomaticPathTrigger(DriverCMD);
  AutoBallTrigger = new AutomaticBallTrigger(DriverCMD);
  

  TeleopModes.push_back(AutoPathTest);
  TeleopModes.push_back(AutoBall);
  TeleopModes.push_back(AutoShoot);
  TeleopModes.push_back(Manual);
  TeleopTriggers.push_back(AutoShootTrigger);
  TeleopTriggers.push_back(AutoBallTrigger);
  TeleopTriggers.push_back(AutoPathTestTrigger);


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
  //MecanumDrive->FieldOrientedDrive();
  //MecanumDrive->leftBack.Set(1);
}

void Robot::TeleopInit() 
{
  // std::string name = TeleopController->nextOp()->name;
  // frc::SmartDashboard::PutString("Next Op", name);
  // frc::SmartDashboard::PutBoolean("manual", Manual->interruptible);
  // frc::SmartDashboard::PutBoolean("test1", Teleop1->interruptible);
  Nav.ResetYaw();
  Nav.setCommandYaw(Nav.getYaw());
}

void Robot::TeleopPeriodic() 
{
  Nav.Update(); // do not remove this, it must be called

  //MecanumDrive->FieldOrientedDrive(); //Field oriented drive code in drivebase is trash, needs to be refactored
  OdometryController->updatePose();
  //double speed = (double)(DriverCMD->bTestButton(9)) * .25;
  //frc::SmartDashboard::PutBoolean("button pressed", DriverCMD->bTestButton(9));
  //frc::SmartDashboard::PutNumber("hopper speed", speed);
  //FeederController->SpinHopper(speed);
  //MecanumDrive->DriveMPS(14, 1.5, 30, 0); //STRICTLY TESTING, REMOVE THIS
  //MecanumDrive->Drive(DriverCMD->fMoveForward(), DriverCMD->fMoveSideways(), DriverCMD->fRotate(), 0);
}

void Robot::DisabledInit() 

{
  // OdometryController->OdometryPeriodicThread.~thread();
}

void Robot::DisabledPeriodic() {

}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
