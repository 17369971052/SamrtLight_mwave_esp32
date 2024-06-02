#include "bsp_servo.h"

Servo myservo; // 创建舵机对象
int pos = 0;   // 舵机位置变量
int servoPin;  // 舵机连接的引脚

void servo_setup(int pin)
{
  servoPin = pin;
  myservo.attach(servoPin); // 将舵机对象附加到对应的引脚
}

/*
* 舵机开灯
*/
int light_turn_on()
{
  servo_setup(SERVO_PIN);
  myservo.write(LIGHT_ON_ANGLE);
  delay(5);
}
/*
* 舵机关灯
*/
int light_turn_off()
{
  servo_setup(SERVO_PIN);
  myservo.write(LIGHT_OFF_ANGLE);
  delay(5);
}

