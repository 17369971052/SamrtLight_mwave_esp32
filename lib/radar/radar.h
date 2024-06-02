#ifndef _RADAR_H
#define _RADAR_H

#include <Arduino.h>

#define radar_pin 4         // 雷达引脚
#define threshold_level 10  // 雷达灵敏度（值增大时降低）

/*
*  Radar.h
* 人体感应数据读取
*/
int getdata(void);
/*
* 人体感应数据处理判断
*/
int getresp(void);


#endif // !_RADAR_H
