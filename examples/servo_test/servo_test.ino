
/*!
   file servo_test.ino
   DFR0587 Gravity: I2C DC Motor/Stepper Motor Driver
   Connect this module to Arduino board via I2C bus, and plug in external power supply.
   The servo will rotate to the position of 30 degree,then it rotate to the position of 90 degree.
   The module has 16 I2C addresses, these addresses are:
   PCA_Address1  0x40   A3 = 0  A2 = 0 A1 = 0  A0 = 0
   PCA_Address2  0x41   A3 = 0  A2 = 0 A1 = 0  A0 = 1
   PCA_Address3  0x42   A3 = 0  A2 = 0 A1 = 1  A0 = 0
   PCA_Address4  0x43   A3 = 0  A2 = 0 A1 = 1  A0 = 1
   PCA_Address5  0x44   A3 = 0  A2 = 1 A1 = 0  A0 = 0
   PCA_Address6  0x45   A3 = 0  A2 = 1 A1 = 0  A0 = 1
   PCA_Address7  0x46   A3 = 0  A2 = 1 A1 = 1  A0 = 0
   PCA_Address8  0x47   A3 = 0  A2 = 1 A1 = 1  A0 = 1
   PCA_Address9  0x48   A3 = 1  A2 = 0 A1 = 0  A0 = 0
   PCA_Address10  0x49   A3 = 1  A2 = 0 A1 = 0  A0 = 1
   PCA_Address11  0x4A   A3 = 1  A2 = 0 A1 = 1  A0 = 0
   PCA_Address12  0x4B   A3 = 1  A2 = 0 A1 = 1  A0 = 1
   PCA_Address13  0x4C   A3 = 1  A2 = 1 A1 = 0  A0 = 0
   PCA_Address14  0x4D   A3 = 1  A2 = 1 A1 = 0  A0 = 1
   PCA_Address15  0x4E   A3 = 1  A2 = 1 A1 = 1  A0 = 0
   PCA_Address16  0x4F   A3 = 1  A2 = 1 A1 = 1  A0 = 1
  
   Copyright    [DFRobot](http://www.dfrobot.com), 2016
   Copyright    GNU Lesser General Public License
   version  V0.1
   date  2019-2-11
*/

#include <DFRobot_Stepper_Motor.h>
#include "Arduino.h"
#include "Wire.h"

DFRobot_Stepper_Motor motor(PCA_Address16);

void setup() {
    Serial.begin(115200);
    Wire.begin();
    while(!motor.available()){                //Begin return True if succeed, otherwise return False
        delay(2000);
        Serial.println("PCA9685 init failed");
    }
    //motor.reset();
}

void loop() {
    motor.servo(PCA_S5, 30);//control the servo of pin S5 to rotate to the position of 30 degree.
    delay(1000);
    motor.servo(PCA_S5, 60);//control the servo of Pin S5 to rotate to the position of 60 degree.
    delay(1000);
    motor.servo(PCA_S5, 90);//control the servo of Pin S5 to rotate to the position of 90 degree.
    delay(1000);
    motor.servo(PCA_S5, 120);//control the servo of Pin S5 to rotate to the position of 120 degree.
    delay(1000);
    motor.servo(PCA_S5, 150);//control the servo of Pin S5 to rotate to the position of 150 degree.
    delay(1000);
    motor.servo(PCA_S5, 180);//control the servo of Pin S5 to rotate to the position of 180 degree.
    delay(1000);

}
