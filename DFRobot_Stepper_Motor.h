#ifndef DFRobot_Stepper_Motor_H
#define DFRobot_Stepper_Motor_H
#include <Arduino.h>
#include <Wire.h>


enum eAddress{
    PCA_Address1 = 0x40, PCA_Address2 = 0x41,
    PCA_Address3 = 0x42, PCA_Address4 = 0x43,
    PCA_Address5 = 0x44, PCA_Address6 = 0x45,
    PCA_Address7 = 0x46, PCA_Address8 = 0x47,
    PCA_Address9 = 0x48, PCA_Address10 = 0x49, 
    PCA_Address11 = 0x4A, PCA_Address12 = 0x4B,
    PCA_Address13 = 0x4C, PCA_Address14 = 0x4D,
    PCA_Address15 = 0x4E, PCA_Address16 = 0x4F,
    PCA_Address17 = 0x50, PCA_Address18 = 0x51,
    PCA_Address19 = 0x52, PCA_Address20 = 0x53,
    PCA_Address21 = 0x54, PCA_Address22 = 0x55,
    PCA_Address23 = 0x56, PCA_Address24 = 0x57,
    PCA_Address25 = 0x58, PCA_Address26 = 0x59, 
    PCA_Address27 = 0x5A, PCA_Address28 = 0x5B,
    PCA_Address29 = 0x5C, PCA_Address30 = 0x5D,
    PCA_Address31 = 0x5E, PCA_Address32 = 0x5F,
    PCA_Address33 = 0x60, PCA_Address34 = 0x61,
    PCA_Address35 = 0x62, PCA_Address36 = 0x63,
    PCA_Address37 = 0x64, PCA_Address38 = 0x65,
    PCA_Address39 = 0x66, PCA_Address40 = 0x67,
    PCA_Address41 = 0x68, PCA_Address42 = 0x69, 
    PCA_Address43 = 0x6A, PCA_Address44 = 0x6B,
    PCA_Address45 = 0x6C, PCA_Address46 = 0x6D,
    PCA_Address47 = 0x6E, PCA_Address48 = 0x6F,
    PCA_Address49 = 0x70, PCA_Address50 = 0x71,
    PCA_Address51 = 0x72, PCA_Address52 = 0x73,
    PCA_Address53 = 0x74, PCA_Address54 = 0x75,
    PCA_Address55 = 0x76, PCA_Address56 = 0x77,
    PCA_Address57 = 0x78, PCA_Address58 = 0x79, 
    PCA_Address59 = 0x7A, PCA_Address60 = 0x7B,
    PCA_Address61 = 0x7C, PCA_Address62 = 0x7D,
    PCA_Address63 = 0x7E, PCA_Address64 = 0x7F
};

#define DFROBOT_PCA_MODE1   0x00
#define DFROBOT_PCA_MODE2   0x01
#define DFROBOT_PCA_SUBADR1   0x02
#define DFROBOT_PCA_SUBADR2   0x03
#define DFROBOT_PCA_SUBADR3   0x04
#define DFROBOT_PCA_PRESCALE   0xFE
#define DFROBOT_PCA_LED0_ON_L   0x06
#define DFROBOT_PCA_LED0_ON_H   0x07
#define DFROBOT_PCA_LED0_OFF_L   0x08
#define DFROBOT_PCA_LED0_OFF_H   0x09
#define DFROBOT_PCA_ALL_LED_ON_L   0xFA
#define DFROBOT_PCA_ALL_LED_ON_H   0xFB
#define DFROBOT_PCA_ALL_LED_OFF_L   0xFC
#define DFROBOT_PCA_ALL_LED_OFF_H   0xFD
           
#define DFROBOT_PCA_STP_CHA_L   2047
#define DFROBOT_PCA_STP_CHA_H   4095
           
#define DFROBOT_PCA_STP_CHB_L   1
#define DFROBOT_PCA_STP_CHB_H   2047
           
#define DFROBOT_PCA_STP_CHC_L   1023
#define DFROBOT_PCA_STP_CHC_H   3071
           
#define DFROBOT_PCA_STP_CHD_L   3071
#define DFROBOT_PCA_STP_CHD_H   1023
           
#define DFROBOT_PCA_BYG_CHA_L   3071
#define DFROBOT_PCA_BYG_CHA_H   1023
           
#define DFROBOT_PCA_BYG_CHB_L   1023
#define DFROBOT_PCA_BYG_CHB_H   3071
           
#define DFROBOT_PCA_BYG_CHC_L   4095
#define DFROBOT_PCA_BYG_CHC_H   2047
           
#define DFROBOT_PCA_BYG_CHD_L   2047
#define DFROBOT_PCA_BYG_CHD_H   4095

    /**
     * The user can choose the step motor model.
     */
enum eStepper { 
    //% block="42"
    PCA_Ste1 = 1,
    //% block="28"
    PCA_Ste2 = 2
};

/**
* The user can select the 8 steering gear controller.
*/
enum eServos {
    PCA_S0 = 0x01,
    PCA_S1 = 0x02,
    PCA_S2 = 0x03,
    PCA_S3 = 0x04,
    PCA_S4 = 0x05,
    PCA_S5 = 0x06,
    PCA_S6 = 0x07,
    PCA_S7 = 0x08
};

/**
* The user selects the 4-way dc motor.
*/
enum eMotors {
    PCA_M1 = 0x1,
    PCA_M2 = 0x2,
    PCA_M3 = 0x3,
    PCA_M4 = 0x4,
    PCA_ALL = 0x5
};

/**
* The user defines the motor rotation direction.
*/
enum eDir {
    //% blockId="CW" block="CW"
    PCA_CW = 1,
    //% blockId="CCW" block="CCW"
    PCA_CCW = -1,
};

/**
* The user can select a two-path stepper motor controller.
*/
enum eSteppers {
    PCA_M1_M2 = 0x1,
    PCA_M3_M4 = 0x2
};

enum eStepper_Status{
    eStepper_ok,
    eStepper_InitError,
    eStepper_WriteRegError,
    eStepper_WriteBufferError,
    eStepper_ReadRegError,
};

class DFRobot_Stepper_Motor
{
    public:
    
    DFRobot_Stepper_Motor(eAddress i2cAddr);
    ~DFRobot_Stepper_Motor();
    
    eStepper_Status lastOperateStatus;
    
    void    servo(eServos index, int degree),
            motorRun(eMotors index, eDir direction, int speed),
            stepperStep(eSteppers index, eDir direction, int step),
            stepperTurn(eSteppers index, eDir direction, double turn),
            stepperTurn(eSteppers index, eDir direction, int turn),
            motorStop(eMotors index),
            reset();

    bool    available();
    

    private:
    
    int    i2cRead(int addr, int reg);
    uint8_t i2cAddr;
    
    void   i2cWrite(int addr, int reg, int value),
           i2cWriteBuffer(int addr, unsigned char *p, int len),
           initPCA9685(),
           setFreq(int freq),
           setPwm(int channel, int on, int off),
           setStepper42(int index, bool dir);
    
    bool   scan(), initialized;

};

#endif
