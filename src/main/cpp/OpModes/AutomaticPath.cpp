// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "OpModes/AutomaticPath.h"

AutomaticPath::AutomaticPath(Robot * pRobot, std::vector<frc::Pose2d*> waypoints, Drivebase * MecanumDrive, OdometryTest * OdometryController)
{
    name = "autoTrench";
    timesRun = 0;
    this->waypoints = waypoints;
    this->pRobot = pRobot;
    this->MecanumDrive = MecanumDrive;
    this->OdometryController = OdometryController;
    this->waypointIndex = 0;
    PathDebug = new Debug{"/Paths/"};
}

void AutomaticPath::Start()
{
    timesRun++;
}

void AutomaticPath::Run()
{
    frc::SmartDashboard::PutNumber("autoTrench start times run", timesRun);
}

bool AutomaticPath::Complete()
{
    return false;
}

//Calculates distance to next waypoint
float AutomaticPath::distanceToNextWaypoint(frc::Pose2d * waypoint)
{
    float xCurrent = OdometryController->getX();
    float yCurrent = OdometryController->getY();
    float xWaypoint = (float)waypoint->Translation().X();
    float yWaypoint = (float)waypoint->Translation().Y();
    float dX = xCurrent - xWaypoint;
    float dY = yCurrent - yWaypoint;
    //the most efficient function in existance. Probably could do everything without square roots honestly
    float distance = sqrt((dX * dX + dY * dY));
    PathDebug->PutNumber("Distance", distance);
    PathDebug->PutNumber("TargetX", xWaypoint);
    PathDebug->PutNumber("TargetY", yWaypoint);
    PathDebug->PutNumber("CurrentX", xCurrent);
    PathDebug->PutNumber("CurrentY", yCurrent);
    return distance;
}

//Return robot's angle to next waypoint using the nav gyro
float AutomaticPath::angleToNextWaypoint(frc::Pose2d * waypoint)
{
    float xCurrent = OdometryController->getX();
    float yCurrent = OdometryController->getY();
    float xWaypoint = (float)waypoint->Translation().X();
    float yWaypoint = (float)waypoint->Translation().Y();
    float robotHeading = OdometryController->getYaw();
    float alpha = atan2((yWaypoint - yCurrent), (xWaypoint - xCurrent)) * 180/3.14159265358979;
    float beta = 90 - alpha;
    float clockwiseAngleToWaypoint = robotHeading + beta;
    float counterclockwise = 360 - clockwiseAngleToWaypoint;
    PathDebug->PutNumber("Angle", counterclockwise);
    return normalize360(counterclockwise);
    //I know this function is unreadable but it probably works so just ctrl-C ctrl-V
}

//Returns true if robot is pretty close to angle it needs to be at for the next waypoint
bool AutomaticPath::atHeading(frc::Pose2d * waypoint)
{
    if((float)waypoint->Rotation().Degrees() > OdometryController->getYaw() - 2 &&
       (float)waypoint->Rotation().Degrees() < OdometryController->getYaw() + 2)
    {
        //Don't need to rotate (close enough to heading)
        return true;
    }
    else
    {
        //Need to rotate 
        return false;
    }
}

//Move to the next waypoint, return true when done with last waypoint
bool AutomaticPath::moveToNextWaypoint(float speedMultiplier, float rotationMultiplier)
{
    //When we reach the waypoint we delete it from the waypoint array.
    float smallDistance1 = 0.05;
    float smallDistance2 = 0.1; //this should be bigger than smallDistance1
    float angle = angleToNextWaypoint(waypoints[waypointIndex]);
    float speed = speedMultiplier;
    if(waypointIndex == waypoints.size() - 1) {
        float distance = distanceToNextWaypoint(waypoints[waypointIndex]);
        //When we start getting close to the last waypoint, slow down a bit
        if(distance < smallDistance2) {
            speed /= 2;
        }
    }

    //If at the correct heading this becomes 0, if not it is scaled to the rotation speed
    float rotate = (int)!atHeading(waypoints[waypointIndex]) * rotationMultiplier;
    MecanumDrive->PolarDrive(speed, angle, rotate, 0);


    //If we are pretty close to the current waypoint, move to the next one
    if(distanceToNextWaypoint(waypoints[waypointIndex]) < smallDistance1) {
        if(waypointIndex != waypoints.size() - 1)
        {
            //go to next waypoint
            waypointIndex++;
        }
        else
        {
            //we've done it boys
            waypointIndex = 0;
            return true;
        }  
    }
    
    return false;
}

//Normalizes an angle (in degrees) to be from 0 to 360
float AutomaticPath::normalize360(float angle)
{
    float newAngle = angle + 3600;
    newAngle = fmod(newAngle, 360);
    return newAngle;
}