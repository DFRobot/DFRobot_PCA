import smbus
import time

class STEPPER:
    
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

    _MODE1  = 0x00
    _MODE2  = 0x01
    _SUBADR1  = 0x02
    _SUBADR2  = 0x03
    _SUBADR3  = 0x04
    _PRESCALE  = 0xFE
    _LED0_ON_L  = 0x06
    _LED0_ON_H  = 0x07
    _LED0_OFF_L  = 0x08
    _LED0_OFF_H  = 0x09
    _ALL_LED_ON_L  = 0xFA
    _ALL_LED_ON_H  = 0xFB
    _ALL_LED_OFF_L  = 0xFC
    _ALL_LED_OFF_H  = 0xFD
    
    _STP_CHA_L  = 2047
    _STP_CHA_H  = 4095
    
    _STP_CHB_L  = 1
    _STP_CHB_H  = 2047
    
    _STP_CHC_L  = 1023
    _STP_CHC_H  = 3071
    
    _STP_CHD_L  = 3071
    _STP_CHD_H  = 1023
    
    
    _BYG_CHA_L  = 3071
    _BYG_CHA_H  = 1023
    
    _BYG_CHB_L  = 1023
    _BYG_CHB_H  = 3071
    
    _BYG_CHC_L  = 4095
    _BYG_CHC_H  = 2047
    
    _BYG_CHD_L  = 2047
    _BYG_CHD_H  = 4095

    M1 = 0x1
    M2 = 0x2
    M3 = 0x3
    M4 = 0x4
    ALL = 0x5
    
    S0 = 0x01
    S1 = 0x02
    S2 = 0x03
    S3 = 0x04
    S4 = 0x05
    S5 = 0x06
    S6 = 0x07
    S7 = 0x08
    
    M1_M2 = 0x1
    M3_M4 = 0x2
    
    CW = 1
    CCW = -1


    def __init__(self, bus, addr):
        self.i2cbus=smbus.SMBus(bus)
        self.i2cAddr = addr
    
    def begin(self):
        if not self.scan():
            return False
        return True
    
    def servo(self, servos_index, degree):
        if self.begin() == True:
            self.initPCA9685()

        v_us = (degree * 10 + 600)
        value = v_us * 4095 / (1000000 / 50)
        self.setPwm(8 - servos_index, 0, value)

    def motorRun(self, motors_index, dir_direction, speed):
        if self.begin() == True:
            self.initPCA9685()
        speed = speed * 16 * dir_direction
        if (speed >= 4096):
            speed = 4095
        if (speed <= -4096):
            speed = -4095
        if (motors_index > 5 or motors_index <= 0):
            return
        pn = 0
        pp = 0
        
        if(motors_index == 1):
            pp = 9;
            pn = 8;
        elif(motors_index == 2):
            pp = 10
            pn = 11
        elif(motors_index == 3):
            pp = 13
            pn = 12
        elif(motors_index == 4):
            pp = 14
            pn = 15
        if (speed >= 0):
            self.setPwm(pp, 0, speed)
            self.setPwm(pn, 0, speed)
        else:
            self.setPwm(pp, 0, 0)
            self.setPwm(pn, 0, -speed)

    def stepperDegree(self, steppers_index, dir_direction, degree):
        if self.begin() == True:
            self.initPCA9685()
        self.setStepper(steppers_index, dir_direction > 0);
        if (degree == 0):
            return
        time.sleep( (50 * degree) / (360 * 50))
        if (steppers_index == 1):
            self.motorStop(self.M1)
            self.motorStop(self.M2)
        else:                   
            self.motorStop(self.M3)
            self.motorStop(self.M4)

    def stepperTurn(self, steppers_index, dir_direction, double_turn):
        self.stepperDegree(steppers_index, dir_direction, (double_turn * 360))

    def stepperTurn(self, steppers_index, dir_direction, turn):
        self.stepperDegree(steppers_index, dir_direction, turn * 360)

    def motorStop(self, motors_index):
        pn = 0
        pp = 0
        
        if(motors_index == 1):
            pp = 9;
            pn = 8;
        elif(motors_index == 2):
            pp = 10
            pn = 11
        elif(motors_index == 3):
            pp = 13
            pn = 12
        elif(motors_index == 4):
            pp = 14
            pn = 15
        self.setPwm(pp, 0, 0)
        self.setPwm(pn, 0, 0)

    def i2cWriteBuffer(self, channel, p, len):
        self.i2cbus.write_i2c_block_data(self.i2cAddr, (self._LED0_ON_L + 4 * channel), p)

    
    def i2cWrite(self, reg, value):
        self.i2cbus.write_byte_data(self.i2cAddr, reg, value)
    
    def i2cRead(self, reg):
        return self.i2cbus.read_byte_data(self.i2cAddr, reg)

    def initPCA9685(self):
        self.i2cWrite(self._MODE1, 0x00)
        self.setFreq(50)
        self.initialized = True
    
    def setFreq(self, freq):
        prescaleval = 25000000
        prescaleval /= 4096
        prescaleval /= freq
        prescaleval -= 1
        
        prescale = prescaleval
        oldmode = self.i2cRead(self._MODE1)
        newmode = (oldmode & 0x7F) | 0x10
        self.i2cWrite(self._MODE1, newmode)
        self.i2cWrite(self._PRESCALE, 0x84)
        self.i2cWrite(self._MODE1, oldmode)
        time.sleep(0.005)
        self.i2cWrite(self._MODE1, oldmode | 0xa1)
        
    def setPwm(self, channel, on, off):
        if (channel < 0 or channel > 16):
            return
        
        buf = []
        buf.append(on & 0xff)
        buf.append((on >> 8) & 0xff)
        buf.append(off & 0xff)
        buf.append((off >> 8) & 0xff)
        self.i2cWriteBuffer(channel, buf, 4)
    
    def setStepper42(self, index, dir):
        if (index == 1):
            if (dir):
                self.setPwm(10, self._BYG_CHA_L, self._BYG_CHA_H)
                self.setPwm(8, self._BYG_CHB_L, self._BYG_CHB_H)
                self.setPwm(9, self._BYG_CHC_L, self._BYG_CHC_H)
                self.setPwm(11, self._BYG_CHD_L, self._BYG_CHD_H)
            else:
                self.setPwm(10, self._BYG_CHC_L, self._BYG_CHC_H)
                self.setPwm(8, self._BYG_CHD_L, self._BYG_CHD_H)
                self.setPwm(9, self._BYG_CHA_L, self._BYG_CHA_H)
                self.setPwm(11, self._BYG_CHB_L, self._BYG_CHB_H)
        else:
            if (dir):
                self.setPwm(14, self._BYG_CHA_L, self._BYG_CHA_H)
                self.setPwm(12, self._BYG_CHB_L, self._BYG_CHB_H)
                self.setPwm(13, self._BYG_CHC_L, self._BYG_CHC_H)
                self.setPwm(15, self._BYG_CHD_L, self._BYG_CHD_H)
            else:
                self.setPwm(14, self._BYG_CHC_L, self._BYG_CHC_H)
                self.setPwm(12, self._BYG_CHD_L, self._BYG_CHD_H)
                self.setPwm(13, self._BYG_CHA_L, self._BYG_CHA_H)
                self.setPwm(15, self._BYG_CHB_L, self._BYG_CHB_H)

    def scan(self):
        try:
            self.i2cbus.read_byte(self.i2cAddr)
            return True
        except:
            print("I2C init fail")
            return False

    def reset(self):
        self.i2cWrite(self._MODE1, 0x00)
        self.i2cWrite(self._MODE2, 0x04)


