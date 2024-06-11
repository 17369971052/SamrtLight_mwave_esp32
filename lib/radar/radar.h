#ifndef _RADAR_H
#define _RADAR_H

#include <Arduino.h>


#define radar_pin 4         // 雷达引脚
#define WINDOW_SIZE 8       //算法窗口大小(可调试)


/*
*  Radar.h
* 人体感应数据读取
*/
int getdata(void);
/*
* 人体感应数据处理判断
*/
int getresp(void);
/*
* 人体感应数据处理算法
* 移动平均算法
*/
int movingAverage(void);

#endif // !_RADAR_H
