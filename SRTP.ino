#include <Servo.h>

#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>


int REC_PIN=11;            //红外接收器OUTPUT端接在pin11
int ENA=5;                 //定义数字接口
int IN1=6;
int IN2=7;
int ENB=8;
int IN3=9;
int IN4=10;
int TrigPin = 12; 
int EchoPin = 13;

IRrecv irrecv(REC_PIN);   //定义IRrecv对象来接收红外线信号
Servo esc;
decode_results results;  //解码结果放在decode_results构造的对象results里
float distanceNEW=0,distanceOLD=0;                

void setup() {
  
  Serial.begin(9600);
  pinMode(ENA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);     //数字IO口输入输出模式定义，假设左边为A12，右边为B34
  pinMode(11,OUTPUT);      //设置11口为红外输出端口
  pinMode(TrigPin,OUTPUT);
  pinMode(EchoPin,INPUT);
  Serial.println("Ultrasonic sensor:");
  esc.attach(3);
  esc.writeMicroseconds(2000);
  Serial.print("max");
  delay(1000);
  esc.writeMicroseconds(1000);
  delay(2000);
  esc.writeMicroseconds(2000);
  Serial.print("end");
  irrecv.enableIRIn();     //启动红外解码
}

void findKG(){
   digitalWrite(TrigPin, LOW);
   delayMicroseconds(2);
   digitalWrite(TrigPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(TrigPin, LOW);
    // 检测脉冲宽度，并计算出距离
   distanceNEW = pulseIn(EchoPin, HIGH) / 58.00;
   if(distanceNEW>200)distanceNEW=distanceOLD;
   else if(distanceOLD==0){
    distanceOLD=distanceNEW;
   }
   else if(distanceOLD-distanceNEW>=1||distanceNEW-distanceOLD>=1){
    Serial.println("KongGu");
   }
   distanceOLD=distanceNEW;
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
   esc.writeMicroseconds(1500);
   if(irrecv.decode(&results)){                //解码成功，收到一组红外线信号，把数据放入results变量中
       Serial.print("1");
       Serial.println(results.value);
       if(results.value==16724175){            //确认接收到按键1的编码，执行前进命令
            Forward();      
            Serial.println(results.value);              
       }
           
       else if(results.value==16718055){       //确认接收到按键2的编码，执行后退命令
            Back();
            Serial.println(results.value);                 
       }
          
       else if(results.value==16743045){       //确认接受到按键3的编码，执行左转命令
            Left();           
            Serial.println(results.value);                
       }
       
       else if(results.value==16716015){       //确认接受到按键4的编码，执行右转命令
          
            Right();      
            Serial.println(results.value);           
       }
          
       else if(results.value==16726215){       //确认接受到按键5的编码，执行刹车命令
            Stop();
 
            Serial.print(results.value);                 
       } 
       
       irrecv.resume();                        //接收下一个值                    
   }            
   delay(60); //延时，做一个简单的消抖
   findKG();
 }
 
