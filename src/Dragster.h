/*
 * This file is a part of Dragster car set library.
 *
 * Declares the Dragster class used to perform basic interactions
 * with the robot (https://amperka.ru/product/dragster)
 *
 * © Amperka LLC (https://amperka.com, dev@amperka.com)
 * 
 * Author: Harry Morgan <morgan@amperka.ru>
 * Refactored by: Yury Botov (by@amperka.com)
 * License: GPLv3, all text here must be included in any redistribution.
 */

#ifndef __DRAGSTER_H__
#define __DRAGSTER_H__

#include <Arduino.h>

constexpr byte SWAP_LEFT = 0b00000010;
constexpr byte SWAP_RIGHT = 0b00000001;
constexpr byte SWAP_BOTH = 0b00000011;

// Motor start rotation then PWM value more then PWM_OF_START_MOVING
constexpr byte PWM_OF_START_MOVING = 25;

// Motor type constants for different sets, use: `Dragster dragster(DRAGSTER_1);`
constexpr byte DRAGSTER_1 = 80;
constexpr byte DRAGSTER_2 = 255;

class Dragster {
public:
    Dragster();
    Dragster(byte upperLimit);
    Dragster(byte upperLimit, byte lowerForwardLimit, byte lowerBackwardLimit);
    void begin();
    void begin(int direction);
    void defineMotorType(byte upperLimit, byte lowerForwardLimit, byte lowerBackwardLimit);
    void drive(int left, int right);
    void driveF(float left, float right);
    void encodersBegin(void (*left)(), void (*right)());
    bool readButton();
    void led(int state);

private:
    void driveMotor(int speed, int swapped, byte dir, byte drv);
    void probeMotorType(void);

    byte _swappedLeft = 1;
    byte _swappedRight = 0;

    byte _upperLimit;
    byte _lowerForwardLimit;
    byte _lowerBackwardLimit;

    bool _motorsUnknown = true;
};

#endif //__DRAGSTER_H__
