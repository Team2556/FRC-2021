// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "OpModes/AutomaticPath.h"

AutomaticPath::AutomaticPath(Robot * pRobot, std::vector<frc::Pose2d*> waypoints, Drivebase * MecanumDrive, Odometry * OdometryController, double speedMultiplier, double rotationMultiplier)
{
    name = "autoTrench";
    timesRun = 0;
    this->waypoints = waypoints;
    this->pRobot = pRobot;
    this->MecanumDrive = MecanumDrive;
    this->OdometryController = OdometryController;
    this->waypointIndex = 0;
    this->speedMultiplier = speedMultiplier;
    this->rotationMultiplier = rotationMultiplier;
    PathDebug = new Debug{"/Paths/"};
}

void AutomaticPath::Start()
{
    complete = false;
    timesRun++;
}

void AutomaticPath::Run()
{
    frc::SmartDashboard::PutNumber("autoTrench start times run", timesRun);
    complete = moveToNextWaypoint();
}

bool AutomaticPath::Complete()
{
    return complete;
}

//Calculates distance to next waypoint
double AutomaticPath::distanceToNextWaypoint(frc::Pose2d * waypoint)
{
    double xCurrent = OdometryController->getX();
    double yCurrent = OdometryController->getY();
    double xWaypoint = (double)waypoint->Translation().X();
    double yWaypoint = (double)waypoint->Translation().Y();
    double dX = xCurrent - xWaypoint;
    double dY = yCurrent - yWaypoint;
    //the most efficient function in existance. Probably could do everything without square roots honestly
    double distance = sqrt((dX * dX + dY * dY));
    PathDebug->PutNumber("Distance", distance);
    PathDebug->PutNumber("TargetX", xWaypoint);
    PathDebug->PutNumber("TargetY", yWaypoint);
    PathDebug->PutNumber("CurrentX", xCurrent);
    PathDebug->PutNumber("CurrentY", yCurrent);
    return distance;
}

//Return robot's angle to next waypoint using the nav gyro
double AutomaticPath::angleToNextWaypoint(frc::Pose2d * waypoint)
{
    double xCurrent = OdometryController->getX();
    double yCurrent = OdometryController->getY();
    double xWaypoint = (double)waypoint->Translation().X();
    double yWaypoint = (double)waypoint->Translation().Y();
    double robotHeading = OdometryController->getYaw();
    double alpha = atan2((yWaypoint - yCurrent), (xWaypoint - xCurrent)) * 180/3.14159265358979;
    double beta = 90 - alpha;
    double clockwiseAngleToWaypoint = robotHeading + beta;
    double counterclockwise = 360 - clockwiseAngleToWaypoint;
    double finalAngle = OdometryController->normalize360(counterclockwise);
    PathDebug->PutNumber("Angle", finalAngle);
    return finalAngle;
    //I know this function is unreadable but it probably works so just ctrl-C ctrl-V
}

//Returns true if robot is pretty close to angle it needs to be at for the next waypoint
bool AutomaticPath::atHeading(frc::Pose2d * waypoint)
{
    if((double)waypoint->Rotation().Degrees() > OdometryController->getYaw() - 2 &&
       (double)waypoint->Rotation().Degrees() < OdometryController->getYaw() + 2)
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
bool AutomaticPath::moveToNextWaypoint()
{
    //When we reach the waypoint we delete it from the waypoint array.
    double smallDistance1 = 0.05;
    double smallDistance2 = 0.1; //this should be bigger than smallDistance1
    double angle = angleToNextWaypoint(waypoints[waypointIndex]);
    double speed = speedMultiplier;
    if(waypointIndex == (int)(waypoints.size() - 1)) {
        double distance = distanceToNextWaypoint(waypoints[waypointIndex]);
        //When we start getting close to the last waypoint, slow down a bit
        if(distance < smallDistance2) {
            speed /= 2;
        }
    }

    //If at the correct heading this becomes 0, if not it is scaled to the rotation speed
    double rotate = (int)!atHeading(waypoints[waypointIndex]) * rotationMultiplier;
    MecanumDrive->PolarDrive(speed, angle, rotate, 0);


    //If we are pretty close to the current waypoint, move to the next one
    if(distanceToNextWaypoint(waypoints[waypointIndex]) < smallDistance1) {
        if(waypointIndex != (int)(waypoints.size() - 1))
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
