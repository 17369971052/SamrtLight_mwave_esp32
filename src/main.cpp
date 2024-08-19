#include "mqtt.h"
#include "radar.h"
#include "bsp_servo.h"

extern PubSubClient client;

void setup()
{
    Serial.begin(115200); // 需要修改
    // Serial1.begin(115200, SERIAL_8N1, 16, 17);
    pinMode(4, INPUT);
    servo_setup(SERVO_PIN);
    pinMode(SERVO_PIN, INPUT);
    initMQTTClient();
}

void loop()
{

    int resp = getresp();
    // int resp = 1;
    int values[] = {resp};
    const char *properties[] = {"resp"};
    reportDeviceValues("mwaveradar", properties, values, sizeof(values) / sizeof(values[0]));
    printf("report  success ! \n");
    delay(3000);
    light_control(resp);
    printf("control  success ! ");
}