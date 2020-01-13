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
    _upperLimit = 80;
    _lowerForwardLimit = 25;
    _lowerBackwardLimit = 25;
}

Dragster::Dragster(byte upperLimit, byte lowerForwardLimit, byte lowerBackwardLimit) {
    defineMotorType(upperLimit, lowerForwardLimit, lowerBackwardLimit);
}

void Dragster::defineMotorType(byte upperLimit, byte lowerForwardLimit, byte lowerBackwardLimit) {
    _upperLimit = upperLimit;
    _lowerForwardLimit = lowerForwardLimit;
    _lowerBackwardLimit = lowerBackwardLimit;
    _motorsUnknown = false;
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
    if (_motorsUnknown && (left != 0 || right != 0))
        probeMotorType();
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

// initialise counters
static byte counter = 0;
void leftEncoder(void) { counter++; }
void rightEncoder(void) { counter++; }

void Dragster::probeMotorType(void) {
    // connect encoders
    encodersBegin(leftEncoder, rightEncoder);
    // set small voltage to motors
    digitalWrite(4, _swappedRight);
    digitalWrite(7, _swappedLeft);
    analogWrite(5, 50);
    analogWrite(6, 50);
    // wait 0.3c
    delay(300);
    // stop motors, disconnect encoders
    analogWrite(5, 0);
    analogWrite(6, 0);
    detachInterrupt(2);
    detachInterrupt(3);
    // motor type selection
    if(counter > 2) {
        defineMotorType(80, 25, 25); // 4 Ohm motors
    } else {
        defineMotorType(255, 25, 25); // 16+ Ohm motors
    }
    _motorsUnknown = false;
}
