// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "OpModes/AutomaticPath.h"

AutomaticPath::AutomaticPath(Robot * pRobot, std::vector<frc::Pose2d*> waypoints, Drivebase * MecanumDrive, Odometry * OdometryController)
{
    name = "autoTrench";
    timesRun = 0;
    this->waypoints = waypoints;
    this->pRobot = pRobot;
    this->MecanumDrive = MecanumDrive;
    this->OdometryController = OdometryController;
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

float AutomaticPath::distanceToNextWaypoint(frc::Pose2d * waypoint)
{
    float xCurrent = OdometryController->getX();
    float yCurrent = OdometryController->getY();
    float xWaypoint = (float)waypoint->Translation().X();
    float yWaypoint = (float)waypoint->Translation().Y();
    float dX = xCurrent - xWaypoint;
    float dY = yCurrent - yWaypoint;
    float distance = sqrt((dX * dX + dY * dY));
    return distance;
}

float AutomaticPath::angleToNextWaypoint(frc::Pose2d * waypoint)
{
    float xCurrent = OdometryController->getX();
    float yCurrent = OdometryController->getY();
    float xWaypoint = (float)waypoint->Translation().X();
    float yWaypoint = (float)waypoint->Translation().Y();
    float robotHeading = OdometryController->getYaw();
    float alpha = atan2((yWaypoint - yCurrent), (xWaypoint - xCurrent)) * 180/M_PI;
    float beta = 90 - alpha;
    float clockwiseAngleToWaypoint = robotHeading + beta;
    float counterclockwise = 360 - clockwiseAngleToWaypoint;
    return normalize360(counterclockwise);
    //I know this function is unreadable but it probably works so just ctrl-C ctrl-V
}

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

void AutomaticPath::moveToNextWaypoint()
{
    //When we reach the waypoint we delete it from the waypoint array.
    float smallDistance1 = 2;
    float smallDistance2 = 3; //this should be bigger than smallDistance1
    if(distanceToNextWaypoint(waypoints[0]) < smallDistance1) {
        waypoints.erase(waypoints.begin());
    }
    float angle = angleToNextWaypoint(waypoints[0]);
    float speed = 0.3;
    if(waypoints.size() == 1) {
        float distance = distanceToNextWaypoint(waypoints[0]);
        if(distance < smallDistance2) {
            speed = 0.2;
        }
    }

    float rotate = (int)!atHeading(waypoints[0]) * 0.5;

    MecanumDrive->PolarDrive(speed, angle, rotate, 0);
}

float AutomaticPath::normalize360(float angle)
{
    float newAngle = angle + 3600;
    newAngle = fmod(newAngle, 360);
    return newAngle;
}