#ifndef SERVO_H
#define SERVO_H

#include <ESP32Servo.h>
#include <Arduino.h>
#include "mqtt.h"
#include "radar.h"

#define SERVO_PIN 5         //舵机引脚
#define LIGHT_ON_ANGLE 45   //舵机开灯角度
#define LIGHT_OFF_ANGLE 135 //舵机关灯角度


#define SERVO_PIN 5
#define LIGHT_ON_SATUS 1
#define LIGHT_OFF_SATUS 0

void light_control(int r);

void servo_setup(int pin);
void servo_turn_on();
void servo_turn_off();

void light_turn_on();
void light_turn_off();
#endif // SERVO_H