// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "rev/ColorSensorV3.h"

#include "Utilities/Debug.h"

class ControlPanel {
 public:
  ControlPanel();

  //Necessary Functions
  bool RotatePanel(); //Rotates the control panel 3 times, returns true when done rotating
  bool RotatePanelToColor(std::string color); //Rotate the control panel until it's at the specified color.
  std::string GetGameColor(); //Get the color that the control panel needs to stop on according to Game Data
  std::string GetSeenColor(); //Get the color that the control panel is currently at (color sensor)


  Debug ControlPanelDebug{"/Subsystems/ControlPanel"};

 private:
  
  //Define a color sensor here. Rev Color Sensor V3 I think
};
