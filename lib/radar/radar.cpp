#include "radar.h"

#include <stdio.h>

// 初始化数组用于存储最近的感应值
int sensorValues[WINDOW_SIZE];
int currentIndex = 0;
int sum = 0;

int movingAverage(void) {
    // 当前窗口未满，直接返回当前值，或平均已有的值
    if (currentIndex < WINDOW_SIZE) 
    {
        return currentIndex ? sum / currentIndex : sensorValues[0];
    }
    else
    {
        // 移除最早的一个值，加入新的值，然后计算平均
        sum -= sensorValues[currentIndex % WINDOW_SIZE]; // 移除旧值
        sum += sensorValues[currentIndex % WINDOW_SIZE] = sensorValues[currentIndex]; // 更新并加入新值
        currentIndex = (currentIndex + 1) % WINDOW_SIZE; // 更新索引
        return sum / WINDOW_SIZE; // 返回平均值
    }
}
//根据高低电平输入返回人体检测数据
int getdata(void)
{
  int r=0;
  int val = digitalRead(radar_pin);
  if(val==LOW)
  {
    r = 0;
  }
  else
  {
    r = 1;
  }
  return(r);
  delay(2);
}

//分析结果优化预测值（可进行灵敏度调节）
int getresp(void)
{
  int rawSensorValue = getdata(); // 请替换为实际的传感器读取逻辑

  // 存储读取的值
  sensorValues[currentIndex] = rawSensorValue;
  
  // 计算并打印移动平均值
  int stableValue = movingAverage();
  printf("Raw Value: %d, Stable Value: %d\n", rawSensorValue, stableValue);
  
  // 适当延时以模拟实时读取（根据实际需求调整）
  // 注意：在实际应用中，延时可能需要替换为更高效的事件驱动或定时器机制
  delay(100); // 假定的延时函数，具体实现取决于平台
  return(stableValue);
}

