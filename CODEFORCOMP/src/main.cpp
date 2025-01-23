/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\tavishi                                          */
/*    Created:      Sat Jan 18 2025                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    18, 19, 17, 20  
// Controller1          controller                    
// Intake               motor         1               
// Ramp                 motor         15              
// Lift                 motor         5               
// MogoMech             digital_out   A               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

bool MogoMechActive = false;
competition Competition;

void pre_auton(void) {
  vexcodeInit();
}


void usercontrol(void) {
  if(Controller1.ButtonA.pressing()) {
      while(Controller1.ButtonA.pressing()) {
        wait(10, msec);
      }
      MogoMechActive = !MogoMechActive;
      MogoMech.set(MogoMechActive);
      }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  // Set up callbacks for autonomous and driver control periods.
  //Drivetrain.setDriveVelocity(5, percent);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
  
}