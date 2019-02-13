
/*!
   file motor_test.ino
   DFR0587 Gravity: I2C DC Motor/Stepper Motor Driver
   Connect this module to Arduino board via I2C bus, and plug in external power supply. 
   This demo can be used to control motor.
   The module has 16 I2C addresses, these addresses are:
   Address1  0x40   A3 = 0  A2 = 0 A1 = 0  A0 = 0
   Address2  0x41   A3 = 0  A2 = 0 A1 = 0  A0 = 1
   Address3  0x42   A3 = 0  A2 = 0 A1 = 1  A0 = 0
   Address4  0x43   A3 = 0  A2 = 0 A1 = 1  A0 = 1
   Address5  0x44   A3 = 0  A2 = 1 A1 = 0  A0 = 0
   Address6  0x45   A3 = 0  A2 = 1 A1 = 0  A0 = 1
   Address7  0x46   A3 = 0  A2 = 1 A1 = 1  A0 = 0
   Address8  0x47   A3 = 0  A2 = 1 A1 = 1  A0 = 1
   Address9  0x48   A3 = 1  A2 = 0 A1 = 0  A0 = 0
   Address10  0x49   A3 = 1  A2 = 0 A1 = 0  A0 = 1
   Address11  0x4A   A3 = 1  A2 = 0 A1 = 1  A0 = 0
   Address12  0x4B   A3 = 1  A2 = 0 A1 = 1  A0 = 1
   Address13  0x4C   A3 = 1  A2 = 1 A1 = 0  A0 = 0
   Address14  0x4D   A3 = 1  A2 = 1 A1 = 0  A0 = 1
   Address15  0x4E   A3 = 1  A2 = 1 A1 = 1  A0 = 0
   Address16  0x4F   A3 = 1  A2 = 1 A1 = 1  A0 = 1
  
   Copyright    [DFRobot](http://www.dfrobot.com), 2018
   Copyright    GNU Lesser General Public License
   version  V0.1
   date  2019-2-11
*/

#include <Stepper_Motor.h>
#include "Arduino.h"
#include "Wire.h"

Stepper_Motor motor;

void setup() {
    Serial.begin(115200);
    Wire.begin();
    motor.setI2cAddr(Address16);
    motor.motorRun(M3, CCW, 200);//control the motor M3 to rotate anticlockwise at the speed of 200 
    //motor.motorStop(M2);//control the motor to stop rotatig.

}

void loop() {

}