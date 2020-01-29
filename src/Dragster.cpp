/*
 * This file is a part of Dragster car set library.
 *
 *
 * © Amperka LLC (https://amperka.com, dev@amperka.com)
 * 
 * Author: Harry Morgan <morgan@amperka.ru>
 * Refactored by: Yury Botov (by@amperka.com)
 * License: GPLv3, all text here must be included in any redistribution.
 */

#include "Dragster.h"

Dragster::Dragster() {
    // default parameters for 3-4 Ohm motors
    setMotorLimits(MMAX_3_OHM, PWM_OF_START_MOVING, PWM_OF_START_MOVING);
}

Dragster::Dragster(byte motorUpperLimit) {
    setMotorLimits(motorUpperLimit, PWM_OF_START_MOVING, PWM_OF_START_MOVING);
}

Dragster::Dragster(byte motorUpperLimit, byte motorLowerForwardLimit, byte motorLowerBackwardLimit) {
    setMotorLimits(motorUpperLimit, motorLowerForwardLimit, motorLowerBackwardLimit);
}

void Dragster::setMotorLimits(byte motorUpperLimit, 
    byte motorLowerForwardLimit, byte motorLowerBackwardLimit) {
    _upperLimit = motorUpperLimit;
    _lowerForwardLimit = motorLowerForwardLimit;
    _lowerBackwardLimit = motorLowerBackwardLimit;
}

void Dragster::begin() {
    pinMode(4, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);

    pinMode(10, INPUT);
    pinMode(13, OUTPUT);
}

void Dragster::begin(int direction) {
    if (direction & SWAP_LEFT) {
        _swappedLeft = 0;
    }
    if (direction & SWAP_RIGHT) {
        _swappedRight = 1;
    }
    begin();
}

void Dragster::drive(int left, int right) {
    driveMotor(left, _swappedLeft, 7, 6);
    driveMotor(right, _swappedRight, 4, 5);
}

void Dragster::driveF(float left, float right) {
    drive((int)(left * 255.0), (int)(right * 255.0));
}

void Dragster::encodersBegin(void (*left)(), void (*right)()) {
    attachInterrupt(2, left, CHANGE);
    attachInterrupt(3, right, CHANGE);
}

bool Dragster::readButton() {
    return digitalRead(10);
}

void Dragster::led(int state) {
    digitalWrite(13, state);
}

void Dragster::driveMotor(int speed, int swapped, byte dir, byte drv) {
    if (swapped)
        speed = -speed;
    if (speed == 0) {
        analogWrite(drv, 0);
    } else if (speed > 0) {
        digitalWrite(dir, HIGH);
        analogWrite(drv, map(speed, 0, 255, _lowerForwardLimit, _upperLimit));
    } else {
        digitalWrite(dir, LOW);
        analogWrite(drv, map(-speed, 0, 255, _lowerBackwardLimit, _upperLimit));
    }
}
