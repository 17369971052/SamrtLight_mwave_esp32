#include "bsp_servo.h"

Servo myservo; // 创建舵机对象
int pos = 0;   // 舵机位置变量
int servoPin;  // 舵机连接的引脚
int sta = 0;

void servo_setup(int pin)
{
  servoPin = pin;
  myservo.attach(servoPin); // 将舵机对象附加到对应的引脚
}

/*
* 舵机开灯
*/
void light_turn_on()
{
  servo_setup(SERVO_PIN);
  myservo.write(LIGHT_ON_ANGLE);
  delay(5);
}
/*
* 舵机关灯
*/
void light_turn_off()
{
  //servo_setup(SERVO_PIN);
  myservo.write(LIGHT_OFF_ANGLE);
  delay(5);
}

void light_control(int r)
{
    if(r == 0)
    {
      if(sta == LIGHT_ON_SATUS)
      {
        light_turn_off();
        printf("Light OFF!");
      }
      sta = LIGHT_OFF_SATUS;
      delay(10);
    }
    else if( r == 1)
    {
      if(sta == LIGHT_OFF_SATUS)
      {
        light_turn_on();
        printf("Light ON!");
      }
      sta=LIGHT_ON_SATUS;
      delay(10);
    }
}