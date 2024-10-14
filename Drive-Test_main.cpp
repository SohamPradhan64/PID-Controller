/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Mon Oct 14 2024                                         */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// Define your global instances of motors and other devices here
bool resetDriveSensors = false;
int desiredValue = 0;
int desiredTurnValue = 0;
bool enablePID = true;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

// Function to handle PID control for driving
int drivePID() {
  while(enablePID) {
    // Example PID control logic would go here

    // Check if resetDriveSensors is true
    if (resetDriveSensors) {
      // Reset sensors, adjust values
      // This is a placeholder; you would actually reset your encoders/gyros here
      resetDriveSensors = false;
    }

    // Calculate necessary drive and turn values based on desiredValue and desiredTurnValue
    // Then update motor power accordingly

    // Insert PID calculations and motor control here

    vex::task::sleep(20); // Sleep to prevent wasted resources
  }

  return 0; // End of task
}

void autonomous(void) {
  vex::task hello(drivePID);  // Start the drivePID task

  resetDriveSensors = true;
  desiredValue = 300;
  desiredTurnValue = 600;
  vex::task::sleep(1000);  // Sleep for a second

  resetDriveSensors = true;
  desiredValue = 300;
  desiredTurnValue = 300;
  // Adjust values for different part of autonomous routine

  // Add more autonomous commands here as needed
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  enablePID = false;  // Turn off PID for manual control

  // User control code here, inside the loop
  while (1) {
    // This is where you would control the robot using the joystick values

    wait(20, msec); // Sleep the task for a short amount of time to prevent wasted resources
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
