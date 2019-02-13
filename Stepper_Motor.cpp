#include "Stepper_Motor.h"
#include "Arduino.h"
#include "Wire.h"



Stepper_Motor::Stepper_Motor(): initialized(false) {}

Stepper_Motor::~Stepper_Motor() 
{
    this->initialized = false;
}

void Stepper_Motor::setI2cAddr(uint16_t addr)
{
    if(addr == Address1){
        i2caddr = addr;
    }
    else if(addr == Address2){
        i2caddr = addr;
    }
    else if(addr == Address3){
        i2caddr = addr;
    }
    else if(addr == Address4){
        i2caddr = addr;
    }
    else if(addr == Address5){
        i2caddr = addr;
    }
    else if(addr == Address6){
        i2caddr = addr;
    }
    else if(addr == Address7){
        i2caddr = addr;
    }
    else if(addr == Address8){
        i2caddr = addr;
    }
    else if(addr == Address9){
        i2caddr = addr;
    }
    else if(addr == Address10){
        i2caddr = addr;
    }
    else if(addr == Address11){
        i2caddr = addr;
    }
    else if(addr == Address12){
        i2caddr = addr;
    }
    else if(addr == Address13){
        i2caddr = addr;
    }
    else if(addr == Address14){
        i2caddr = addr;
    }
    else if(addr == Address15){
        i2caddr = addr;
    }
    else if(addr == Address16){
        i2caddr = addr;
    }
    else{
        i2caddr = Address16;
    }
}

bool Stepper_Motor::begin()
{
    Wire.begin();
    if (scan() == true)
    {
        
        return true;
    }
    else{
        Serial.println("I2C init fail");
        return false;
    }
}

void Stepper_Motor::servo(eServos index, int degree)
{
    if (!initialized) {
        this->initPCA9685();
    }
    // 100hz
    uint32_t v_us = (degree * 10 + 600); // 0.6ms ~ 2.4ms
    uint32_t value = v_us * 4095 / (1000000 / 50);
    this->setPwm(8 - index, 0, value);
}   

void Stepper_Motor::motorRun(eMotors index, eDir direction, int speed)
{
    if (!initialized) {
        this->initPCA9685();
    }
    speed = speed * 16 * direction; // map 255 to 4096
    if (speed >= 4096) {
        speed = 4095;
    }
    if (speed <= -4096) {
        speed = -4095;
    }
    if (index > 5 || index <= 0)
        return;
    int pn, pp;
    Serial.println(index);
    if(index == 1){
        pp = 9;
        pn = 8;
    }else if(index == 2){
        pp = 10;
        pn = 11;
    }
    else if(index == 3){
        pp = 13;
        pn = 12;
    }
    else if(index == 4){
        pp = 14;
        pn = 15;
    }
    else if(index == 5){
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

void Stepper_Motor::stepperDegree42(eSteppers index, eDir direction, int degree)
{
    if (!initialized) {
        this->initPCA9685();
    }
    // let Degree = Math.abs(degree);
    // Degree = Degree * direction;
    //setFreq(100);````
    this->setStepper42(index, direction > 0);
    if (degree == 0) { 
        return;
    }
    uint32_t Degree = abs(degree);
    delay( (50000 * Degree) / (360 * 50) + 80);
    Serial.println("hello");
    if (index == 1) {
        this->motorStop(M1);
        this->motorStop(M2);
    }else{
        this->motorStop(M3);
        this->motorStop(M4);
    }
}

void Stepper_Motor::stepperTurn42(eSteppers index, eDir direction, double turn)
{
    this->stepperDegree42(index, direction, (int)(turn * 360));
}

void Stepper_Motor::stepperTurn42(eSteppers index, eDir direction, int turn)
{
    this->stepperDegree42(index, direction, turn * 360);
}

void Stepper_Motor::motorStop(eMotors index)
{
    if (index > 5 || index <= 0)
        return;
    int pn, pp;
    //Serial.println(index);
    if(index == 1){
        pp = 9;
        pn = 8;
    }else if(index == 2){
        pp = 10;
        pn = 11;
    }
    else if(index == 3){
        pp = 13;
        pn = 12;
    }
    else if(index == 4){
        pp = 14;
        pn = 15;
    }
    else if(index == 5){
    }
    this->setPwm(pp, 0, 0);
    this->setPwm(pn, 0, 0);
}


void Stepper_Motor::i2cWriteBuffer(int addr, unsigned char *p, int len)
{
    Wire.beginTransmission(addr);
    for(int i=0; i<len; i++)
        Wire.write((uint8_t)p[i]);
    Wire.endTransmission();
}

void Stepper_Motor::i2cWrite(int addr, int reg, int value)
{
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

int Stepper_Motor::i2cRead(int addr, int reg)
{
    uint8_t data;
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(addr, 1);
    data = Wire.read();
    return data;
}

void Stepper_Motor::initPCA9685()
{
    if (scan() == true){
        Wire.begin();
        this->i2cWrite(i2caddr, MODE1, 0x00);
        this->setFreq(50);
        this->initialized = true;//Serial.println(i2caddr);
        //Serial.println("I2C init succeed");
        //Serial.println(i2caddr);
    } else{
        this->initialized = false;
        Serial.print("I2C address is ");Serial.println(i2caddr,HEX);
    }
}

void Stepper_Motor::setFreq(int freq)
{
    uint32_t prescaleval = 25000000;
    prescaleval /= 4096;
    prescaleval /= freq;
    prescaleval -= 1;

    uint32_t prescale = prescaleval;//Math.floor(prescaleval + 0.5);
    uint8_t oldmode = this->i2cRead(i2caddr, MODE1);
    uint8_t newmode = (oldmode & 0x7F) | 0x10; // sleep
    this->i2cWrite(i2caddr, MODE1, newmode); // go to sleep
    this->i2cWrite(i2caddr, PRESCALE, 0x84); // set the prescaler
    this->i2cWrite(i2caddr, MODE1, oldmode);
    delayMicroseconds(5000);
    this->i2cWrite(i2caddr, MODE1, oldmode | 0xa1);
}

void Stepper_Motor::setPwm(int channel, int on, int off)
{
    if (channel < 0 || channel > 15)
        return;
    
    unsigned char buf[5];
    buf[0] = LED0_ON_L + 4 * channel;
    buf[1] = on & 0xff;
    buf[2] = (on >> 8) & 0xff;
    buf[3] = off & 0xff;
    buf[4] = (off >> 8) & 0xff;
    this->i2cWriteBuffer(i2caddr, buf, 5);
}

void Stepper_Motor::setStepper42(int index, bool dir)  
{
    if (index == 1) {
        if (dir) {
            this->setPwm(10, BYG_CHA_L, BYG_CHA_H);
            this->setPwm(8, BYG_CHB_L, BYG_CHB_H);
            this->setPwm(9, BYG_CHC_L, BYG_CHC_H);
            this->setPwm(11, BYG_CHD_L, BYG_CHD_H);
        } else {
            this->setPwm(10, BYG_CHC_L, BYG_CHC_H);
            this->setPwm(8, BYG_CHD_L, BYG_CHD_H);
            this->setPwm(9, BYG_CHA_L, BYG_CHA_H);
            this->setPwm(11, BYG_CHB_L, BYG_CHB_H);
        }
    } else {
        if (dir) {
            this->setPwm(14, BYG_CHA_L, BYG_CHA_H);
            this->setPwm(12, BYG_CHB_L, BYG_CHB_H);
            this->setPwm(13, BYG_CHC_L, BYG_CHC_H);
            this->setPwm(15, BYG_CHD_L, BYG_CHD_H);
        
        
        } else {
            this->setPwm(14, BYG_CHC_L, BYG_CHC_H);
            this->setPwm(12, BYG_CHD_L, BYG_CHD_H);
            this->setPwm(13, BYG_CHA_L, BYG_CHA_H);
            this->setPwm(15, BYG_CHB_L, BYG_CHB_H);
        }
    }
}

bool Stepper_Motor::scan()
{
    Wire.beginTransmission(i2caddr);
    if (Wire.endTransmission() == 0){
        return true;
    }
    return false;
}


