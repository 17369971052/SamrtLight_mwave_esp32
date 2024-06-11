#ifndef CONTROL_H
#define CONTROL_H

#include <Arduino.h>
#include "mqtt.h"
#include "radar.h"
#include "bsp_servo.h"

#define SERVO_PIN 5
#define LIGHT_ON_SATUS 1
#define LIGHT_OFF_SATUS 0

void light_control(int r);

#endif // CONTROL_H