//8,9-2,3
#include<SoftwareSerial.h>
SoftwareSerial bt(6,5);
//unsigned long previousMillis = 0UL;
//unsigned long interval = 100UL;

void quad(int a,int b,int c,int d){
  digitalWrite(2,a);
  digitalWrite(3,b);
  digitalWrite(8,c);
  digitalWrite(7,d);
}

void myDelay(int del) {
  unsigned long myPrevMillis = millis();
  while (millis()- myPrevMillis <= del);
}

void setup() {
  Serial.begin(9600);
  bt.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(7,OUTPUT);
}

void loop(){
 if(bt.available()>0){
  char c = bt.read();
  Serial.println(c);
  switch (c)
  {
    case 'L' :
      quad(0,1,0,1);
      Serial.println("Left");
      bt.println("Left");
      myDelay(100);
      break;
    case 'R' :
      Serial.println("Right");
      bt.println("Right");
      quad(1,0,1,0);
      //dd();
      myDelay(100);
      break;
    case 'F' ://actually back as on 27 FEB 2023
      Serial.println("Left");
      bt.println("Left");
      quad(0,1,1,0);
      //dd();
      myDelay(100);
      break;
    case 'B' :
      quad(1,0,0,1);
      Serial.println("Backward");
      bt.println("Backward");
      myDelay(100);
      break;
    default:
      Serial.println("Not in use");
      quad(0,0,0,0);
    }
  }
  else{
    quad(0,0,0,0);
  }
}