#include "Dragster.h"

Dragster::Dragster() { }
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
	swappedLeft = 1;
  }
  if (direction & SWAP_RIGHT) {
	swappedRight = 1;
  }
  begin();
}
void Dragster::drive(int left, int right) {
  if (swappedLeft) {
	  left = -left;
  }
  if (left > 0) {
	digitalWrite(7, HIGH);
	analogWrite(6, left);
  } else {
	digitalWrite(7, LOW);
	analogWrite(6, -left);
  }
  if (swappedRight) {
	  right = -right;
  }
  if (right > 0) {
	digitalWrite(4, HIGH);
	analogWrite(5, right);
  } else {
	digitalWrite(4, LOW);
	analogWrite(5, -right);
  }
}
void Dragster::driveF(float left, float right) {
  if (swappedLeft) {
	  left = -left;
  }
  if (left > 0) {
	digitalWrite(7, HIGH);
	if (left > 1) left = 1;
	analogWrite(6, left * 255);
  } else {
	digitalWrite(7, LOW);
	if (left < -1) left = -1;
	analogWrite(6, -left * 255);
  }
  if (swappedRight) {
	  right = -right;
  }
  if (right > 0) {
	digitalWrite(4, HIGH);
	if (right > 1) right = 1;
	analogWrite(5, right * 255);
  } else {
	digitalWrite(4, LOW);
	if (right < -1) right = -1;
	analogWrite(5, -right * 255);
  }
}
void Dragster::encodersBegin(void (*left)(), void (*right)()) {
  attachInterrupt(2, left, CHANGE);
  attachInterrupt(3, right, CHANGE);
}
void Dragster::leftEncoder(void (*left)(), int param) {
  attachInterrupt(2, left, param);
}
void Dragster::rightEncoder(void (*right)(), int param) {
  attachInterrupt(3, right, param);
}
bool Dragster::readButton() {
  return digitalRead(10);
}
void Dragster::led(int state) {
  digitalWrite(13, state);
}