#ifndef SERVO_H
#define SERVO_H

#include <ESP32Servo.h>
#include <Arduino.h>
#define SERVO_PIN 5
#define LIGHT_ON_ANGLE 45
#define LIGHT_OFF_ANGLE 135


void servo_setup(int pin);
void servo_turn_on();
void servo_turn_off();

int light_turn_on();
int light_turn_off();
#endif // SERVO_H