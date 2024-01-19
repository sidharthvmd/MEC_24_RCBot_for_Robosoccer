
#define D2 2
#define D3 3
volatile long StartTimeFB = 0;
volatile long CurrentTimeFB = 0;
volatile long PulsesFB = 0;
int PulseWidthFB = 0;

volatile long StartTimeLR = 0;
volatile long CurrentTimeLR = 0;
volatile long PulsesLR = 0;
int PulseWidthLR = 0;

void setup() {
  //set up the serial monitor, pin mode, and external interrupt.
  Serial.begin(9600);
  pinMode(D2, INPUT_PULLUP);
  pinMode(D3, INPUT_PULLUP);
  pinMode(5,OUTPUT);//fwdr
  pinMode(6,OUTPUT);//bwdr
  pinMode(7,OUTPUT);//fwdl
  pinMode(8,OUTPUT);//bwdl
  allout();
  attachInterrupt(digitalPinToInterrupt(D2),PulseTimer_FB,CHANGE);
  attachInterrupt(digitalPinToInterrupt(D3),PulseTimer_LR,CHANGE);
}

void allout(){
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
    digitalWrite(8,LOW);
}

void loop() {
  if(PulseWidthFB==0||PulseWidthLR==0){
    allout();
  }
  //only save pulse lengths that are less than 2000 microseconds
  if (PulsesFB < 2000){
    PulseWidthFB = PulsesFB/10;
  }
  else if (PulsesLR < 2000){
    PulseWidthLR = PulsesLR/10;
  } 
  if (PulseWidthFB<130){
    Serial.println("Hello");
    digitalWrite(6,HIGH);
    digitalWrite(8,HIGH);
  }
  else if (PulseWidthFB>170){
    digitalWrite(5,HIGH);
    digitalWrite(7,HIGH);
    Serial.println("Hello");
  }
  else if (PulseWidthLR<120){
    digitalWrite(6,HIGH);
    digitalWrite(7,HIGH);
    Serial.println("Hello");
  }
  else if (PulseWidthLR>170){
    digitalWrite(5,HIGH);
    digitalWrite(8,HIGH);
    Serial.println("Hello");
  }
  else{
    allout();
  }
  //Serial.println(PulseWidthFB);
  Serial.println(PulseWidthLR);
}


void PulseTimer_FB(){
  //measure the time between interrupts
  CurrentTimeFB = micros();
  if (CurrentTimeFB > StartTimeFB){
    PulsesFB = CurrentTimeFB - StartTimeFB;
    StartTimeFB = CurrentTimeFB;
  }
}

void PulseTimer_LR(){
  //measure the time between interrupts
  CurrentTimeLR = micros();
  if (CurrentTimeLR > StartTimeLR){
    PulsesLR = CurrentTimeLR - StartTimeLR;
    StartTimeLR = CurrentTimeLR;
  }
}
