
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
  pinMode(5, OUTPUT);  //fwdr
  pinMode(6, OUTPUT);  //bwdr
  pinMode(7, OUTPUT);  //fwdl
  pinMode(8, OUTPUT);  //bwdl
  run(0,0,0,0);
  attachInterrupt(digitalPinToInterrupt(D2), PulseTimer_FB, CHANGE);
  attachInterrupt(digitalPinToInterrupt(D3), PulseTimer_LR, CHANGE);
}

void run(int a, int b, int c, int d) {
  digitalWrite(5, a);
  digitalWrite(6, b);
  digitalWrite(7, c);
  digitalWrite(8, d);
}

void loop() {
  if (PulseWidthFB == 0 || PulseWidthLR == 0) {
    run(0, 0, 0, 0);
  }
  //only save pulse lengths that are less than 2000 microseconds
  if (PulsesFB < 2000) {
    PulseWidthFB = PulsesFB / 10;
  } else if (PulsesLR < 2000) {
    PulseWidthLR = PulsesLR / 10;
  }
  if (PulseWidthFB < 140) {
    run(0, 1, 0, 1);
    Serial.println(1);
  } else if (PulseWidthFB > 150) {
    run(1, 0, 1, 0);
    Serial.println(2);
  } else if (PulseWidthLR < 140) {
    run(0, 1, 1, 0);
    Serial.println(3);
  } else if (PulseWidthLR > 150) {
    run(1,0,0,1);
    Serial.println(4);
  }
  else{
    run(0,0,0,0);
  }
}


void PulseTimer_FB() {
  //measure the time between interrupts
  CurrentTimeFB = micros();
  if (CurrentTimeFB > StartTimeFB) {
    PulsesFB = CurrentTimeFB - StartTimeFB;
    StartTimeFB = CurrentTimeFB;
  }
}

void PulseTimer_LR() {
  //measure the time between interrupts
  CurrentTimeLR = micros();
  if (CurrentTimeLR > StartTimeLR) {
    PulsesLR = CurrentTimeLR - StartTimeLR;
    StartTimeLR = CurrentTimeLR;
  }
}