//By using this program, you can initialize electronic speed controller
//Connect the signal wire to pin 3

#include<Servo.h>
Servo esc;

void setup() {
  esc.attach(3);
  esc.writeMicroseconds(2000);//set the max
  Serial.print("max");
  delay(1000);
  esc.writeMicroseconds(1000);//set the min
  delay(2000);
  esc.writeMicroseconds(2000);
  Serial.print("end");
}

void loop() {
  esc.writeMicroseconds(1400);
}
