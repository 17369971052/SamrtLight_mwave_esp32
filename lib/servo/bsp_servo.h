#ifndef SERVO_H
#define SERVO_H

#include <ESP32Servo.h>
#include <Arduino.h>

#define SERVO_PIN 5
#define LIGHT_ON_ANGLE 45
#define LIGHT_OFF_ANGLE 135
#define LIGHT_ON_SATUS 1
#define LIGHT_OFF_SATUS 0

void servo_setup(int pin);
void servo_turn_on();
void servo_turn_off();

void light_turn_on();
void light_turn_off();
void light_control(int r);

#endif // SERVO_H