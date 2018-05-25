//This project writed a project that you can use it to send AT instruction to HC-05 using Serial Monitor on arduinoIDE
//Upload the program to arduino before you attach it to HC-05 module
//Press the key on HC-05 before you Power-On it
//AT instructions:
//        AT    
//        AT+NAME= NameYouWant    rename
//        AT+ORGL                 reset
//        ...
// Pin10 as arduino's RX, connect to TXD on HC05
// Pin11 as arduino's TX, connect to RXD on HC05 
#include <SoftwareSerial.h> 
SoftwareSerial BT(10, 11);
char val;
void setup() { 
  Serial.begin(38400); 
  Serial.println("BT is ready!"); // HC-05默认，38400 
  BT.begin(38400); 
  } 

void loop() { 
    if (Serial.available()){ 
      val = Serial.read();
      BT.print(val);
     } 
     if (BT.available()) 
     {
      val = BT.read();
      Serial.print(val); 
      }
  } 



