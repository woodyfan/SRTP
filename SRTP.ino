//Now we are using Bluetooth rather than 
//Infrared Ray to control the device
#include <Servo.h>

#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

int ENA=5;                 //定义数字接口
int IN1=6;
int IN2=7;
int ENB=8;
int IN3=9;
int IN4=10;
int TrigPin = 12; 
int EchoPin = 13;
char val=0,state=0;
Servo esc;
float distanceNEW=0,distanceOLD=0;                

void setup() {
  
  Serial.begin(38400);
  pinMode(ENA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);     //数字IO口输入输出模式定义，假设左边为A12，右边为B34
  pinMode(11,OUTPUT);
  pinMode(TrigPin,OUTPUT);//For ultrasonic signal
  pinMode(EchoPin,INPUT);
  esc.attach(3);
  //irrecv.enableIRIn();     //启动红外解码
}
void LightOn(){
  digitalWrite(11,HIGH);
  delay(1000);
  digitalWrite(11,LOW);

  
}
void findKG(){
   digitalWrite(TrigPin, LOW);
   delayMicroseconds(2);
   digitalWrite(TrigPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(TrigPin, LOW);
    // 检测脉冲宽度，并计算出距离
   int distance = pulseIn(EchoPin, HIGH);
   distanceNEW = distance / 58.00;
   //Serial.println(distanceNEW);
   if(distanceNEW>200)distanceNEW=distanceOLD;
   else if(distanceOLD==0){
    distanceOLD=distanceNEW;
   }
   else if(distanceOLD-distanceNEW>=0.5||distanceNEW-distanceOLD>=0.5){
    LightOn();
   }
   distanceOLD=distanceNEW;
   delay(100);
}
/*前进子程序,左正右反，对应按键1*/
void Forward(void){
   digitalWrite(IN1,HIGH);
   digitalWrite(IN2,LOW);
   digitalWrite(IN3,LOW);
   digitalWrite(IN4,HIGH);
   digitalWrite(ENA,HIGH);
   digitalWrite(ENB,HIGH);
}


/*后退子程序，左反右正，对应按键2*/
void Back(void){
   digitalWrite(IN1,LOW);
   digitalWrite(IN2,HIGH);
   digitalWrite(IN3,HIGH);
   digitalWrite(IN4,LOW);
   digitalWrite(ENA,HIGH);
   digitalWrite(ENB,HIGH);
}


/*左转子程序，左反右反，对应按键3*/
void Left(void){
   digitalWrite(IN1,LOW);
   digitalWrite(IN2,HIGH);
   digitalWrite(IN3,LOW);
   digitalWrite(IN4,HIGH);
   digitalWrite(ENA,HIGH);
   digitalWrite(ENB,HIGH);
}


/*右转子程序，左正右正，对应按键4*/
void Right(void){
   digitalWrite(IN1,HIGH);
   digitalWrite(IN2,LOW);
   digitalWrite(IN3,HIGH);
   digitalWrite(IN4,LOW);
   digitalWrite(ENA,HIGH);
   digitalWrite(ENB,HIGH);     
}


/*刹车子程序,对应按键5*/
void Stop(void){  
   digitalWrite(IN1,LOW);
   digitalWrite(IN2,LOW);
   digitalWrite(IN3,LOW);
   digitalWrite(IN4,LOW);
   digitalWrite(ENA,LOW);
   digitalWrite(ENB,LOW);
}

void loop() {
   //esc.writeMicroseconds(2000);
   if(Serial.available()){                //解码成功，收到一组红外线信号，把数据放入results变量中
       state=Serial.read();
   }
   if(state=='2'){            //确认接收到按键2，执行前进命令
            Forward();                    
       }
           
    else if(state=='8'){       //确认接收到按键8，执行后退命令
            Back();                 
       }
          
       else if(state=='4'){       //确认接受到按键4，执行左转命令
            Left();           
       }
       
       else if(state=='6'){       //确认接受到按键6，执行右转命令
            Right();
       }
          
       else if(state=='0'){       //确认接受到按键0，执行刹车命令
            Stop();
       } 
        delay(60); //延时，做一个简单的消抖
        findKG();  //检测空鼓存在性
 }
 
