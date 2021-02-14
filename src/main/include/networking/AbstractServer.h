// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>

using std::string;

class AbstractServer { //HEY YOU! Don't access this as a pointer since destructors are called on the pointer and not what it points to (socket freed in destructor)
  public:
    AbstractServer(string ipaddress, int port, int socketType, int protocol);
    void writeString(string message);
    string readString();
    void acceptWaiting();
    ~AbstractServer(); // free socket here
  private:
    int clientFileDescriptor = -1;
    int fileDescriptor;
};


