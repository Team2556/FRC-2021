// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "networking/TCPServer.h"
#include "networking/TCPSocket.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include "thread"
#include <iostream>
#include <mutex>

using std::exception;

class Jetson {
 public:
  Jetson();
  void testServer();
  float getX();
  float getY();
  float getRotate();
  float getConfidence();
  void setInitialPosition();

  std::thread JetsonReceiverThread;

 private:
  float x;
  float y;
  float rotation;
  float confidence;
  

  void updateJetsonPose();
  std::vector<int> allIndexesOfChar(char character, std::string data);

  std::mutex jetsonMutex;

};
