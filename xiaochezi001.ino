#include <Microduino_Motor.h>
#include <TraceApp.h>
TraceApp obj(Serial, 9600);   //实例化检测对象
#define my_Serial Serial //定义串口通讯为Serial
#define OUT1A 6     //D6，D8控制1A，1B的电机
#define OUT1B 8
#define OUT2A 5     //D5，D7控制2A，2B的电机
#define OUT2B 7
void Go();  //声明函数
void Left();
void Right();
void RightBack();
void LeftBack();
void Stop();
void setup()       //设置
{
  obj.begin();      //初始化,注意:后面不需要再用Serial.begin()!
  Serial.println("init finish");
  my_Serial.begin(9600);//BT通讯波特率
  pinMode(OUT1A, OUTPUT);
  pinMode(OUT1B, OUTPUT);
  pinMode(OUT2A, OUTPUT);
  pinMode(OUT2B, OUTPUT);
}

void loop()
{
  obj.routine();    //尽可能让这一句频繁运行，提高灵敏度
  if (obj.valid())  //检测的物体是否有效
  {
    Serial.print("Obj detected at:");
    Serial.print(obj.getX());  //x坐标
    Serial.print(",");
    Serial.print(obj.getY());  //y坐标
    Serial.print("  with size of:");
    Serial.println(obj.getT()); //物体大小
    int a=obj.getX();  //获取坐标值
    int b=obj.getY();
    int c=obj.getT();
    if(a<185&&b<185)   //判断坐标并执行相应动作，使目标处于视野中央
    {
      Right();
    }
    else if(a>185&&b<185)
    {
      Left();
    }
    else if(a<185&&b>185)
    {
      RightBack();
    }
    else if(a>185&&b>185)
    {
      LeftBack();
    }
    else
    {
      Go();
    }
  }  
  else   //若目标无效
   {
    Serial.println("No obj or too many detected");
     Stop();
   }
  delay(100);  //延时100毫秒
}
void Go()//前进程序
{
  analogWrite(OUT1A, 200);  //用PWM控制电机速度，数值根据具体情况调试
  digitalWrite(OUT1B, LOW);
  analogWrite(OUT2A, 200); 
  digitalWrite(OUT2B, LOW);

}
void Right()//右转程序
{
  analogWrite(OUT1A, 120);
  digitalWrite(OUT1B, LOW);
  analogWrite(OUT2A, 180);
  digitalWrite(OUT2B, LOW);
}

void Left()//左转程序
{
  analogWrite(OUT1A, 180); 
  digitalWrite(OUT1B, LOW);
  analogWrite(OUT2A, 120);
  digitalWrite(OUT2B, LOW);
}
void RightBack()//右后退程序
{
  digitalWrite(OUT1A, LOW);
  analogWrite(OUT1B, 180);
  digitalWrite(OUT2A, LOW);
  analogWrite(OUT2B, 120);
}
void LeftBack()//左后退程序
{
  digitalWrite(OUT1A, LOW);
  analogWrite(OUT1B, 120);
  digitalWrite(OUT2A, LOW);
  analogWrite(OUT2B, 180);
}
void Stop()//停止程序
{
  digitalWrite(OUT1A, LOW);
  digitalWrite(OUT1B, LOW);
  digitalWrite(OUT2A, LOW);
  digitalWrite(OUT2B, LOW);
}
