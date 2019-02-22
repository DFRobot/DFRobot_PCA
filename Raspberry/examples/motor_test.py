# -*- coding: utf-8 -*-

'''
file stepper_test.py
SEN0291 Wattmeter Sensor
This sensor can detect Voltage ,Current,and Power
The module has 16 I2C addresses, these addresses are:
    PCA9685_ADDRESS1  = 0x40
    PCA9685_ADDRESS2  = 0x41
    PCA9685_ADDRESS3  = 0x42
    PCA9685_ADDRESS4  = 0x43
    PCA9685_ADDRESS5  = 0x44
    PCA9685_ADDRESS6  = 0x45
    PCA9685_ADDRESS7  = 0x46
    PCA9685_ADDRESS8  = 0x47
    PCA9685_ADDRESS9  = 0x48
    PCA9685_ADDRESS10  = 0x49
    PCA9685_ADDRESS11  = 0x4A
    PCA9685_ADDRESS12  = 0x4B
    PCA9685_ADDRESS13  = 0x4C
    PCA9685_ADDRESS14  = 0x4D
    PCA9685_ADDRESS15  = 0x4E
    PCA9685_ADDRESS16  = 0x4F
Copyright    [DFRobot](http://www.dfrobot.com), 2018
Copyright    GNU Lesser General Public License
version  V1.0
date  2019-1-30
'''
import time
import sys
sys.path.append('../')
from DFRobot_Stepper_Motor import STEPPER

motor = STEPPER(1, STEPPER.PCA9685_ADDRESS16) 
#begin return True if succeed, otherwise return False
while not motor.begin():
    time.sleep(2)
    print("PCA9685 init failed")

def main():
    while True:
        motor.motorRun(motor.M3, motor.CW, 200)
        time.sleep(2)
        motor.motorRun(motor.M3, motor.CCW, 200)
        time.sleep(2)
        motor.motorStop(motor.M3)
        time.sleep(2)
        #motor.reset()

if __name__ == "__main__":
    main()
