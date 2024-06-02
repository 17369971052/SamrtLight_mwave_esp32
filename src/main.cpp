#include "mqtt.h"
#include "radar.h"


extern PubSubClient client;

void setup()
{
    Serial.begin(115200);//需要修改
    Serial1.begin(115200, SERIAL_8N1, 16, 17);
    pinMode(4, INPUT);
    initMQTTClient();
}

void loop()
{
    int values[] = {getresp()};
    const char *properties[] = {"resp"};
    reportDeviceValues("mwaveradar", properties, values, sizeof(values)/sizeof(values[0]));
    delay(100);
}