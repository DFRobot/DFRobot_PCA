# PCA9685

PCA9685 is a chip based on I2C bus communication.<br>
This library can help you to control motor, servo and stepper motor by PCA9685.<br>
The library is designed for DFR0587 Gravity: I2C DC Motor/Stepper Motor Driver.<br>
Please provide external power for the motor drive plate.<br>

## PCA9685 Library for RaspberryPi
---------------------------------------------------------
Provide a Raspberry Pi library for the Stepper modules.

## Table of Contents

* [Summary](#summary)
* [Feature](#feature)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [Credits](#credits)
<snippet>
<content>

## Summary
This library can help you to control motor, servo and stepper motor by PCA9685.<br>

## Feature
1. External power supply is needed.
2. Support I2C bus communication.
3. Short-circuit A0, A1, A2, A3 to change I2C address.
4. External power supply voltage: 5V~12V.

## Installation

This Sensor should work with Motor Driver on RaspberryPi.<br>
Run the program:
```
$> python DFRobot_INA219_test.py

```

## Methods

```Python
'''
@brief Init The PCA9685

@param bus      I2C bus
@param addr =   PCA9685_ADDRESS1  = 0x40
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
'''
STEPPER(bus, addr)

'''
@brief To judge which address is being used 

@return true if PCA8591 init succeed
@return false if PCA8591 init failed
'''
def begin(self)

'''
@brief Motor rotates at a fixed speed;

@param index = M1,M2,M3,M4,M_ALL
@param direction = CW(clockwise),CCW(counter-clockwise)
@param speed = 0~255
'''
def motorRun(self, motors_index, dir_direction, speed)

'''
@brief Servo rotates to the position of a fixed degree.

@param index =S0,S1,S2,S3,S4,S5,S6,S7
@param degree = 0~180(degree)
'''
def servo(self, servos_index, degree)

'''
@brief Stepper motor rotates by an angle of a fixed degree.

@param index = M1_M2,M3_M4(stepper motor interface)
@param direction = CW(clockwise),CCW(counter-clockwise)
@param degree = 0~360
'''
def stepperDegree42(self, steppers_index, dir_direction, degree)

'''
@brief Stepper motor rotates for fixed turns.

@param index = M1_M2,M3_M4(stepper motor interface)
@param direction = CW(clockwise),CCW(counter-clockwise)
@param turn = 0~10
'''
def stepperTurn(self, steppers_index, dir_direction, double_turn);
def stepperTurn(self, steppers_index, dir_direction, turn);

'''
@brief motor stop rotating.

@param index = M1,M2,M3,M4,M_ALL
'''
def motorStop(self, motors_index)

'''
@brief PCA9685 reset
'''
def reset()

```


## Credits

·author [luoyufeng yufeng.luo@dfrobot.com]
