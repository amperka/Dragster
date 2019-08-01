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

#define SWAP_LEFT 0b00000010
#define SWAP_RIGHT 0b00000001
#define SWAP_BOTH 0b00000011

// Motor type is:
// COMMON: 1.5V (3-4 Ohm)
// GOOD: 3V (6-8 Ohm)
// BEST: 6V (13-16 Ohm)
typedef enum { 
    COMMON = 70,
    GOOD = 140,
    BEST = 255 } MotorType;

// Motor don't rotate with voltage less then
#define LOWER_VOLTAGE_LIMIT 13

class Dragster {
public:
    Dragster();
    void begin();
    void begin(int direction);
    void drive(int left, int right);
    void driveF(float left, float right);
    void encodersBegin(void (*left)(), void (*right)());
    bool readButton();
    void led(int state);

private:
    void driveMotor(int speed, int swapped, byte dir, byte drv);

    byte _swappedLeft = 1;
    byte _swappedRight = 0;
};

#endif //__DRAGSTER_H__
