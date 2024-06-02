/**
 * @file mqtt.h
 * @brief 这个头文件包含了MQTT客户端的声明和一些全局变量的声明。
 *
 * 这个文件包含了以下内容：
 * - 引入了一些必要的库文件，包括Arduino、Wire、WiFi、PubSubClient和ArduinoJson库。
 * - 声明了一些全局变量，包括WiFi的SSID和密码、MQTT服务器的地址和端口、MQTT客户端的ID、用户名和密码。
 * - 声明了一些函数，包括初始化MQTT客户端的函数、订阅命令主题的函数、发送MQTT消息的函数和上报设备属性值的函数。
 */

#include <Arduino.h>
#include <Wire.h>         //Arduino的库文件
#include <WiFi.h>         //ESP32的库文件
#include <PubSubClient.h> //在“管理库”搜索“PubSubClient”，下载库文件
#include <ArduinoJson.h>

// #include "radar.h"


extern const char *ssid;
extern const char *password;
extern const char *mqttServer;
extern const int mqttPort;
extern const char *clientId;
extern const char *mqttUser;
extern const char *mqttPassword;
extern const char *topic_properties_report;
extern const char *topic_commands_request;


// 初始化MQTT客户端
void initMQTTClient();

// 发送MQTT消息，参数包括主题和消息内容
void sendMQTTMessage(const char *topic, const char *message);

// 上报设备的属性值，参数包括服务ID，属性名数组，属性值数组和数组大小
void reportDeviceValues(const char *service_id, const char **properties, int *values, int size);