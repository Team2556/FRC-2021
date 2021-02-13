// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <stdexcept>
#include <string>

using std::exception;
using std::string;

class SocketException : public exception {
  public:
    SocketException(string message) {
        this->message = "SocketException: " + message;
    }

    virtual const char* what() const throw() {
        return message.c_str();
    }
  private:
    string message;
};

