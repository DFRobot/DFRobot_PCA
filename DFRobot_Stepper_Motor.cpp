#include "DFRobot_Stepper_Motor.h"
#include "Arduino.h"
#include "Wire.h"



DFRobot_Stepper_Motor::DFRobot_Stepper_Motor(eAddress i2cAddr): initialized(false)
{
    this->i2cAddr = i2cAddr;
}

DFRobot_Stepper_Motor::~DFRobot_Stepper_Motor() 
{
    this->initialized = false;
}

bool DFRobot_Stepper_Motor::available()
{
    Wire.begin();
    if (scan() == true)
    {
        return true;
    }
    else{
        return false;
    }
}

void DFRobot_Stepper_Motor::servo(eServos index, int degree)
{
    if (!initialized) {
        this->initPCA9685();
    }
    // 100hz
    degree = abs(degree);
    uint32_t v_us = (degree * 10 + 600); // 0.6ms ~ 2.4ms
    uint32_t value = v_us * 4095 / (1000000 / 50);
    this->setPwm(8 - index, 0, value);
}   

void DFRobot_Stepper_Motor::motorRun(eMotors index, eDir direction, int speed)
{
    if (!initialized) {
        this->initPCA9685();
    }
    speed = abs(speed);
    speed = speed * 16 * direction; // map 255 to 4096
    if (speed >= 4096) {
        speed = 4095;
    }
    if (speed <= -4096) {
        speed = -4095;
    }
    if (index > PCA_ALL || index < PCA_M1)
        return;
    int pn, pp;
    if(index == PCA_M1){
        pp = 9;
        pn = 8;
    }else if(index == PCA_M2){
        pp = 11;
        pn = 10;
    }else if(index == PCA_M3){
        pp = 13;
        pn = 12;
    }else if(index == PCA_M4){
        pp = 14;
        pn = 15;
    }else if(index == PCA_ALL){
        motorRun(PCA_M1, direction, speed);
        motorRun(PCA_M2, direction, speed);
        motorRun(PCA_M3, direction, speed);
        motorRun(PCA_M4, direction, speed);
    }
    if (speed >= 0) {
        this->setPwm(pp, 0, speed);
        this->setPwm(pn, 0, speed);
    }
    else{
        this->setPwm(pp, 0, 0);
        this->setPwm(pn, 0, -speed);
    }
}

void DFRobot_Stepper_Motor::stepperStep(eSteppers index, eDir direction, int step)
{
    if (!initialized) {
        this->initPCA9685();
    }
    if (step == 0) { 
        return;
    }
    this->setStepper42(index, direction > 0);
    uint32_t Step = abs(step);
    delay((47000 * Step) / (200 * 50) + 80);
    if (index == 1) {
        this->motorStop(PCA_M1);
        this->motorStop(PCA_M2);
    }else{
        this->motorStop(PCA_M3);
        this->motorStop(PCA_M4);
    }
}

void DFRobot_Stepper_Motor::stepperTurn(eSteppers index, eDir direction, double turn)
{
    this->stepperStep(index, direction, (int)(turn * 200));
}

void DFRobot_Stepper_Motor::stepperTurn(eSteppers index, eDir direction, int turn)
{
    this->stepperStep(index, direction, turn * 200);
}

void DFRobot_Stepper_Motor::motorStop(eMotors index)
{
    if (index > PCA_ALL || index < PCA_M1)
        return;
    int pn, pp;
    if(index == PCA_M1){
        pp = 9;
        pn = 8;
    }else if(index == PCA_M2){
        pp = 11;
        pn = 10;
    }
    else if(index == PCA_M3){
        pp = 13;
        pn = 12;
    }
    else if(index == PCA_M4){
        pp = 14;
        pn = 15;
    }
    else if(index == PCA_ALL){
        motorStop(PCA_M1);
        motorStop(PCA_M2);
        motorStop(PCA_M3);
        motorStop(PCA_M4);
    }
    this->setPwm(pp, 0, 0);
    this->setPwm(pn, 0, 0);
}


void DFRobot_Stepper_Motor::i2cWriteBuffer(int addr, unsigned char *p, int len)
{
    lastOperateStatus = eStepper_WriteBufferError;
    Wire.beginTransmission(addr);
    for(int i=0; i<len; i++)
        Wire.write((uint8_t)p[i]);
    Wire.endTransmission();
    lastOperateStatus = eStepper_ok;
}

void DFRobot_Stepper_Motor::i2cWrite(int addr, int reg, int value)
{
    lastOperateStatus = eStepper_WriteRegError;
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
    lastOperateStatus = eStepper_ok;
}

int DFRobot_Stepper_Motor::i2cRead(int addr, int reg)
{
    lastOperateStatus = eStepper_ReadRegError;
    uint8_t data;
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(addr, 1);
    data = Wire.read();
    return data;
    lastOperateStatus = eStepper_ok;
}

void DFRobot_Stepper_Motor::initPCA9685()
{
    lastOperateStatus = eStepper_InitError;
    if (scan() == true){
        Wire.begin();
        this->i2cWrite(i2cAddr, DFROBOT_PCA_MODE1, 0x00);
        this->setFreq(50);
        this->initialized = true;
    } else{
        this->initialized = false;
        Serial.print("I2C address is ");Serial.println(i2cAddr,HEX);
    }
    lastOperateStatus = eStepper_ok;
}

void DFRobot_Stepper_Motor::setFreq(int freq)
{
    uint32_t prescale = 25000000;

    uint32_t prescaleVal = prescale / 4096 / freq - 1;
    uint8_t oldmode = this->i2cRead(i2cAddr, DFROBOT_PCA_MODE1);
    uint8_t newmode = (oldmode & 0x7F) | 0x10; // sleep
    this->i2cWrite(i2cAddr, DFROBOT_PCA_MODE1, newmode); // go to sleep
    this->i2cWrite(i2cAddr, DFROBOT_PCA_PRESCALE, prescaleVal); // set the prescaler
    this->i2cWrite(i2cAddr, DFROBOT_PCA_MODE1, oldmode);
    delayMicroseconds(5000);
    this->i2cWrite(i2cAddr, DFROBOT_PCA_MODE1, oldmode | 0xa1);
}

void DFRobot_Stepper_Motor::setPwm(int channel, int on, int off)
{
    if (channel < 0 || channel > 15)
        return;
    
    unsigned char buf[5];
    buf[0] = DFROBOT_PCA_LED0_ON_L + 4 * channel;
    buf[1] = on & 0xff;
    buf[2] = (on >> 8) & 0xff;
    buf[3] = off & 0xff;
    buf[4] = (off >> 8) & 0xff;
    this->i2cWriteBuffer(i2cAddr, buf, 5);
}

void DFRobot_Stepper_Motor::setStepper42(int index, bool dir)  
{
    if (index == 1) {
        if (dir) {
            this->setPwm(10, DFROBOT_PCA_BYG_CHA_L, DFROBOT_PCA_BYG_CHA_H);
            this->setPwm(8, DFROBOT_PCA_BYG_CHB_L, DFROBOT_PCA_BYG_CHB_H);
            this->setPwm(9, DFROBOT_PCA_BYG_CHC_L, DFROBOT_PCA_BYG_CHC_H);
            this->setPwm(11, DFROBOT_PCA_BYG_CHD_L, DFROBOT_PCA_BYG_CHD_H);
        } else {
            this->setPwm(10, DFROBOT_PCA_BYG_CHC_L, DFROBOT_PCA_BYG_CHC_H);
            this->setPwm(8, DFROBOT_PCA_BYG_CHD_L, DFROBOT_PCA_BYG_CHD_H);
            this->setPwm(9, DFROBOT_PCA_BYG_CHA_L, DFROBOT_PCA_BYG_CHA_H);
            this->setPwm(11, DFROBOT_PCA_BYG_CHB_L, DFROBOT_PCA_BYG_CHB_H);
        }
    } else {
        if (dir) {
            this->setPwm(15, DFROBOT_PCA_BYG_CHA_L, DFROBOT_PCA_BYG_CHA_H);
            this->setPwm(13, DFROBOT_PCA_BYG_CHB_L, DFROBOT_PCA_BYG_CHB_H);
            this->setPwm(12, DFROBOT_PCA_BYG_CHC_L, DFROBOT_PCA_BYG_CHC_H);
            this->setPwm(14, DFROBOT_PCA_BYG_CHD_L, DFROBOT_PCA_BYG_CHD_H);
        
        
        } else {
            this->setPwm(15, DFROBOT_PCA_BYG_CHC_L, DFROBOT_PCA_BYG_CHC_H);
            this->setPwm(13, DFROBOT_PCA_BYG_CHD_L, DFROBOT_PCA_BYG_CHD_H);
            this->setPwm(12, DFROBOT_PCA_BYG_CHA_L, DFROBOT_PCA_BYG_CHA_H);
            this->setPwm(14, DFROBOT_PCA_BYG_CHB_L, DFROBOT_PCA_BYG_CHB_H);
        }
    }
}

bool DFRobot_Stepper_Motor::scan()
{
    Wire.beginTransmission(i2cAddr);
    if (Wire.endTransmission() == 0){
        return true;
    }
    return false;
}

void DFRobot_Stepper_Motor::reset()
{
    this->i2cWrite(i2cAddr, DFROBOT_PCA_MODE1, 0x00);
    //this->i2cWrite(i2cAddr, DFROBOT_PCA_MODE2, 0x04);
}
