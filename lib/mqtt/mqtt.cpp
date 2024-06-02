
/**
 * @file mqtt.cpp
 * @brief 这个文件包含了MQTT客户端的实现。
 *
 * 这个文件包含了以下内容：
 * - WiFi网络的SSID和密码，用于连接WiFi网络。
 * - MQTT服务器的地址和端口，用于连接MQTT服务器。
 * - MQTT客户端的ID、用户名和密码，用于鉴权。
 * - MQTT的主题，用于发布和订阅消息。
 * - WiFiClient和PubSubClient对象的定义，用于实现MQTT客户端的功能。
 * - JSON文档和缓冲区的大小，用于处理JSON格式的消息。
 * - 初始化MQTT客户端的函数，用于连接WiFi网络和MQTT服务器。

 */

#include "mqtt.h"
#include "radar.h"

/*MQTT连接配置*/
/*-----------------------------------------------------*/
const char *ssid = "HUAWEI nova 5z";                                                            // 接入wifi的名字
const char *password = "56771231";                                                   // 接入wifi的密码
const char *mqttServer = "fcb55bf98b.st1.iotda-device.cn-north-4.myhuaweicloud.com"; // 在华为云IoT的 总览->接入信息->MQTT（1883）后面的网址
const int mqttPort = 1883;
// 以下3个参数可以由HMACSHA256算法生成，为硬件通过MQTT协议接入华为云IoT平台的鉴权依据
const char *clientId = "6659d8d26bc31504f06cc3c3_mwaveradar_0_0_2024061004";
const char *mqttUser = "6659d8d26bc31504f06cc3c3_mwaveradar";
const char *mqttPassword = "cf835d6589d23667d2eb262e1c939b4d532c3199efe095f219a2ee905354f457";

// 华为云IoT的产品->查看->Topic管理->设备上报属性数据的 $oc/devices/{你的设备ID}/sys/properties/report
const char *topic_properties_report = "$oc/devices/6659d8d26bc31504f06cc3c3_mwaveradar/sys/properties/report";

/*-----------------------------------------------------*/

WiFiClient espClient; // ESP32WiFi模型定义MQTT_Init
PubSubClient client(espClient);

// JSON文档的大小
#define JSON_DOC_SIZE = 1024;
// JSON字符串的缓冲区大小
const int JSON_BUFFER_SIZE = 200;

/**
 * @brief 初始化MQTT客户端，连接WiFi网络和MQTT服务器。
 *
 * 此函数将ESP32连接到指定的WiFi网络，并尝试与MQTT服务器建立连接。它设置连接的必要参数，如服务器地址、端口、客户端ID、用户名和密码。它还设置连接的保持活动时间。
 * 如果与MQTT服务器的连接失败，函数将在6秒的延迟后重试。
 * 成功连接到MQTT服务器后，函数将订阅命令主题。
 * @author Abrillant-Lee
 * @date 2024-4-1
 */
void initMQTTClient()
{
    // WiFi网络连接部分
    WiFi.begin(ssid, password); // 开启ESP32的WiFi
    while (WiFi.status() != WL_CONNECTED)
    { // ESP尝试连接到WiFi网络
        delay(3000);
        Serial.println("正在连接wifi.......");
    }
    Serial.println("连接WiFi成功！");

    // MQTT服务器连接部分
    client.setServer(mqttServer, mqttPort); // 设置连接到MQTT服务器的参数

    client.setKeepAlive(60); // 设置心跳时间

    while (!client.connected())
    { // 尝试与MQTT服务器建立连接
        Serial.println("正在通过MQTT连接华为云IoTDA平台...");

        if (client.connect(clientId, mqttUser, mqttPassword))
        {

            Serial.println("连接华为云IoTDA平台成功!");
        }
        else
        {

            Serial.print("连接失败");
            Serial.print(client.state());
            delay(6000);
        }
    }
}

/**
 * @brief 向指定的主题发送MQTT消息。
 *
 * 此函数使用MQTT客户端将消息发布到指定的MQTT主题。
 * 如果消息成功发布，将在串行监视器中打印成功消息。
 * 如果消息发布失败，将在串行监视器中打印错误消息。
 * 在发布消息后，调用`client.loop()`以保持连接活动。
 *
 * @param topic 要发布消息的MQTT主题。
 * @param message 要发布的消息。
 * @date 2024-6-2
 * @author Pete
 */
void sendMQTTMessage(const char *topic, const char *message)
{
    // 发布消息到指定的MQTT主题
    if (client.publish(topic, message) == true)
    {
        // 如果发布成功，打印成功消息
        Serial.println("消息发送成功");
    }
    else
    {
        // 如果发布失败，打印错误消息
        Serial.println("消息发送失败");
    }
    // 调用client.loop()以保持连接活跃
    client.loop();
    Serial.println("-------------");
}

/**
 * @brief 将设备值报告给指定的MQTT服务。
 *
 * 该函数创建一个包含设备值的JSON文档，并将其发送到MQTT主题。
 * 设备值由properties和values数组指定。
 *
 * @param service_id MQTT服务的ID。
 * @param properties 一个字符串数组，表示属性名称。
 * @param values 一个整数数组，表示属性值。
 * @param size properties和values数组的大小。
 */
void reportDeviceValues(const char *service_id, const char **properties, int *values, int size)
{
    DynamicJsonDocument doc(1024);
    JsonObject root = doc.to<JsonObject>();
    JsonArray services = root.createNestedArray("services");
    JsonObject service_1 = services.createNestedObject();
    JsonObject properties_1_1 = service_1.createNestedObject("properties");
    service_1["service_id"] = service_id;

    // 循环设置每个属性和其对应的值
    for (int i = 0; i < size; i++)
    {
        properties_1_1[properties[i]] = values[i];
    }

    char JSONmessageBuffer[JSON_BUFFER_SIZE];
    serializeJson(doc, JSONmessageBuffer);
    Serial.println("正在发送消息到MQTT主题..");
    Serial.println(JSONmessageBuffer);

    sendMQTTMessage(topic_properties_report, JSONmessageBuffer);
}


/**
 * @brief 打印消息和值
 *
 * @param message 消息字符串
 * @param value 值字符串
 *
 * @date 2024-6-2
 * @author Pete
 */
void printMessage(const char *message, const char *value)
{
    Serial.print(message); // 打印消息
    Serial.println(value); // 打印值
}

/**
 * Publishes a response to the specified topic.
 * 发布响应到指定的主题。
 *
 * @param topic The topic to publish the response to.
 *              要发布响应的主题。
 * @param response The response to be published.
 *                 要发布的响应。
 * @return true if the response was published successfully, false otherwise.
 *         如果成功发布响应，则返回true；否则返回false。
 */
bool publishResponse(const char *topic, const char *response)
{
    Serial.print("Topic: ");
    Serial.println(topic);
    Serial.print("Response: ");
    Serial.println(response);
    Serial.print("Client state: ");
    Serial.println(client.state());
    if (client.publish(topic, response))
    {                                                   // 如果发布成功
        printMessage("成功发布响应到命令响应主题", ""); // 打印成功消息
        return true;                                    // 返回true
    }
    else
    {                                                   // 如果发布失败
        printMessage("发布响应到命令响应主题失败", ""); // 打印失败消息
        return false;                                   // 返回false
    }
}
