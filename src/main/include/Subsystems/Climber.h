// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "Utilities/Debug.h"
class Climber {
 public:
  Climber();

  bool ClimberUp(); //Return true when climber is up and robot is ready to climb
  bool Climb(); //Return true when robot has finished climbing


  Debug ClimberDebug{"/Subsystems/Climber"};
 
 private:

  //Define your motors and other climber hardware stuff here


};
