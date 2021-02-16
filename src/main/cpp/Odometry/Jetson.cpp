// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Odometry/Jetson.h"

Jetson::Jetson()
{
    JetsonReceiverThread = std::thread(&Jetson::updateJetsonPose, this);
    JetsonReceiverThread.detach();
}

void Jetson::updateJetsonPose()
{
    TCPServer server{"0.0.0.0", 5801};
    while(true)
    {
        jetsonMutex.lock();
        std::string message = server.readString();
        //std::string message = "0, 12.013, 43.11, 8, 53.9999"; <--- Example Message
        //Extract id from message
        int firstCommaPos = message.find(",");
        int id = std::stoi(message.substr(0, firstCommaPos)); //extracts id string, converts it to int
        std::string data = message.substr(firstCommaPos + 1); //extracts everything after the space following the first comma
        std::vector<int> commaPositions;
        switch(id) {
            case 0:
                //All of this garbage extracts x, y, rotation, and confidence from the message
                commaPositions = allIndexesOfChar(',', message); //Gets index of each comma in the message
                x = std::stof(data.substr(commaPositions[0], commaPositions[1] - (commaPositions[0] + 2)));
                y = std::stof(data.substr(commaPositions[1], commaPositions[2] - (commaPositions[1] + 2)));
                rotation = std::stof(data.substr(commaPositions[2], commaPositions[3] - (commaPositions[2] + 2)));
                confidence = std::stof(data.substr(commaPositions[3]));
                break;
            default:
                std::cout << "We have a significant issue with our Jetson data.";
                break;
        }
        jetsonMutex.unlock();
    }
}

void Jetson::testServer()
{
    // try {
    //     server.acceptWaiting();

    //     frc::SmartDashboard::PutString("Test server", server.readString());

    //     server.writeString("RAWR XD XD");
    // } catch (const exception &e) {
    //     frc::SmartDashboard::PutString("testServerError", e.what());
    // }
}

//Returns all indexes of a character in a string
std::vector<int> Jetson::allIndexesOfChar(char character, std::string data)
{
    std::vector<int> indexArray = {};
    int nextComma = -1;
    while(true)
    {
        nextComma = data.find(character, nextComma + 1);
        if(nextComma == -1) {
            break;
        }
        else {
            indexArray.push_back(nextComma);
        }
    }
    return indexArray;
}

//Get robot's X position according to Jetson
float Jetson::getX()
{
    return x;
}

//Get robot's Y position according to Jetson
float Jetson::getY()
{
    return y;
}

//Get robot's rotation according to Jetson
float Jetson::getRotate()
{
    return rotation;
}

//Get Jetson's confidence
float Jetson::getConfidence()
{
    return confidence;
}