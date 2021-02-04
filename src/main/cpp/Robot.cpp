// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>


void Robot::RobotInit() 
{
  Teleop1 = new TestTeleop1();
  Teleop2 = new TestTeleop2();
  Manual =  new ManualTeleop();
  DriverCMD = new OI();
  TeleopTrigger1 = new TestTrigger1(DriverCMD);
  TeleopTrigger2 = new TestTrigger2(DriverCMD);

  TeleopModes.push_back(Teleop1);
  TeleopModes.push_back(Teleop2);
  TeleopModes.push_back(Manual);
  TeleopTriggers.push_back(TeleopTrigger1);
  TeleopTriggers.push_back(TeleopTrigger2);

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
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
