# -*- coding: utf-8 -*-

'''
file stepper_test.py
SEN0291 Wattmeter Sensor
This sensor can detect Voltage ,Current,and Power
The module has 16 I2C addresses, these addresses are:
    _PCA9685_ADDRESS1  = 0x40
    _PCA9685_ADDRESS2  = 0x41
    _PCA9685_ADDRESS3  = 0x42
    _PCA9685_ADDRESS4  = 0x43
    _PCA9685_ADDRESS5  = 0x44
    _PCA9685_ADDRESS6  = 0x45
    _PCA9685_ADDRESS7  = 0x46
    _PCA9685_ADDRESS8  = 0x47
    _PCA9685_ADDRESS9  = 0x48
    _PCA9685_ADDRESS10  = 0x49
    _PCA9685_ADDRESS11  = 0x4A
    _PCA9685_ADDRESS12  = 0x4B
    _PCA9685_ADDRESS13  = 0x4C
    _PCA9685_ADDRESS14  = 0x4D
    _PCA9685_ADDRESS15  = 0x4E
    _PCA9685_ADDRESS16  = 0x4F
Copyright    [DFRobot](http://www.dfrobot.com), 2018
Copyright    GNU Lesser General Public License
version  V1.0
date  2019-1-30
'''
import time
import sys
sys.path.append('../')
from Stepper_Motor import STEPPER

_PCA9685_ADDRESS1  = 0x40
_PCA9685_ADDRESS2  = 0x41
_PCA9685_ADDRESS3  = 0x42
_PCA9685_ADDRESS4  = 0x43
_PCA9685_ADDRESS5  = 0x44
_PCA9685_ADDRESS6  = 0x45
_PCA9685_ADDRESS7  = 0x46
_PCA9685_ADDRESS8  = 0x47
_PCA9685_ADDRESS9  = 0x48
_PCA9685_ADDRESS10  = 0x49
_PCA9685_ADDRESS11  = 0x4A
_PCA9685_ADDRESS12  = 0x4B
_PCA9685_ADDRESS13  = 0x4C
_PCA9685_ADDRESS14  = 0x4D
_PCA9685_ADDRESS15  = 0x4E
_PCA9685_ADDRESS16  = 0x4F

motor = STEPPER(1, _PCA9685_ADDRESS16) 
#begin return True if succeed, otherwise return False
while not motor.begin():
    time.sleep(2)

def main():
    while True:
        motor.stepperDegree42(motor.M1_M2, motor.CW,  360)
        time.sleep(2)
        motor.stepperTurn42(motor.M1_M2, motor.CCW,  10)
        time.sleep(2)

if __name__ == "__main__":
    main()
