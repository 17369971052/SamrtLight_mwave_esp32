#include "radar.h"

#define radar 4

//根据高低电平输入返回人体检测数据
int getdata(void)
{
  int r=2;
  int val = digitalRead(4);
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
  int res = 2;
  int sum = 0;
  for(int i=0;i<5;i++)
  {
    sum += getdata();
    delay(20);
  }
  printf("sum=%d",sum);
  if(sum == 5)
  {
    res = 1;
  }
  else
  {
    res = 0;
  }
  
  return(res);
}
