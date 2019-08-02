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
    _upperVoltageLimit = UPPER_VOLTAGE_FOR_4_OHMS;
    _lowerClockwiseVoltageLimit = 15; // reduction gear resistivity is different
    _lowerCounterClockwiseVoltageLimit = 21; // in different rotation directions
}

Dragster::Dragster(MotorType type) {
    _upperVoltageLimit = type;
    _lowerClockwiseVoltageLimit = 15;
    _lowerCounterClockwiseVoltageLimit = 21;
}

Dragster::Dragster(MotorType type, byte leftLowerLimit, byte rightLowerLimit) {
    _upperVoltageLimit = type;
    _lowerClockwiseVoltageLimit = leftLowerLimit;
    _lowerCounterClockwiseVoltageLimit = rightLowerLimit;
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
    if (left == 0)
        driveMotor(0, _swappedLeft, 7, 6);
    else if (left > 0)
        driveMotor(map(left, 0, 255, _lowerClockwiseVoltageLimit, (long)_upperVoltageLimit), _swappedLeft, 7, 6);
    else
        driveMotor(map(left, 0, 255, _lowerCounterClockwiseVoltageLimit, (long)_upperVoltageLimit), _swappedLeft, 7, 6);

    if (right == 0)
        driveMotor(0, _swappedRight, 4, 5);
    else if (right > 0)
        driveMotor(map(right, 0, 255, _lowerCounterClockwiseVoltageLimit, (long)_upperVoltageLimit), _swappedRight, 4, 5);
    else
        driveMotor(map(right, 0, 255, _lowerClockwiseVoltageLimit, (long)_upperVoltageLimit), _swappedRight, 4, 5);
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
    if (speed > 0) {
        digitalWrite(dir, HIGH);
        analogWrite(drv, speed);
    } else {
        digitalWrite(dir, LOW);
        analogWrite(drv, -speed);
    }
}
