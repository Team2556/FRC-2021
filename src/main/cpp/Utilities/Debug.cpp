// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Utilities/Debug.h"

Debug::Debug(std::string name) 
{
    table = nt::NetworkTableInstance::GetDefault().GetTable(name);
}

void Debug::PutString(std::string key, std::string value)
{
    table->PutString(key, value);
}

void Debug::PutNumber(std::string key, float value)
{
    table->PutNumber(key, value);
}

void Debug::PutBoolean(std::string key, bool value)
{
    table->PutBoolean(key, value);
}

float Debug::GetNumber(std::string key, float defaultValue)
{
    return table->GetNumber(key, defaultValue);
}
