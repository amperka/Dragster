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

class Dragster {
public:
    Dragster();
    void begin();
    void begin(int direction);
    void drive(int left, int right);
    void driveF(float left, float right);
    void encodersBegin(void (*left)(), void (*right)());
    void leftEncoder(void (*left)(), int param);
    void rightEncoder(void (*left)(), int param);
    bool readButton();
    void waitButton();
    void led(int state);

private:
    void driveOne(int speed, int swapped, byte dir, byte drv);

    byte swappedLeft = 0;
    byte swappedRight = 0;
};

#endif //__DRAGSTER_H__
