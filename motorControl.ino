//------- CONSTANTS
const int TONE = 0;
const int MOTOR_NUMBER = 1;
const char BORDER_CHAR = '\0';

//TODO: REFAC THIS CODE!!!

const int motor1Pin = 2;
const int motor2Pin = 3;
const int motor3Pin = 4;
const int motor4Pin = 5;
const int motor5Pin = 6;
const int motor6Pin = 8;
const int motor7Pin = 9;
const int motor8Pin = 10;
const int motor9Pin = 11;
const int motor10Pin = 12;
const int motor11Pin = 13;

const unsigned long maxMotorSpeed = 10000;
const unsigned int minMotorSpeed = 0;

const long doNotRotate = 500000;

const int serialPollInterval = 5000; //5 msec

//------- VARIABLES

byte motor1State = LOW;   // LOW = off
byte motor2State = LOW;
byte motor3State = LOW;
byte motor4State = LOW;
byte motor5State = LOW;
byte motor6State = LOW;
byte motor7State = LOW;
byte motor8State = LOW;
byte motor9State = LOW;
byte motor10State = LOW;
byte motor11State = LOW;

unsigned long motor1Duration = 100; //microsec
unsigned long motor2Duration = 100;
unsigned long motor3Duration = 100;
unsigned long motor4Duration = 100; 
unsigned long motor5Duration = 100;
unsigned long motor6Duration = 100;
unsigned long motor7Duration = 100; 
unsigned long motor8Duration = 100;
unsigned long motor9Duration = 100;
unsigned long motor10Duration = 100;
unsigned long motor11Duration = 100;

bool turnOffMotor1 = false;
bool turnOffMotor2 = false;
bool turnOffMotor3 = false;
bool turnOffMotor4 = false;
bool turnOffMotor5 = false;
bool turnOffMotor6 = false;
bool turnOffMotor7 = false;
bool turnOffMotor8 = false;
bool turnOffMotor9 = false;
bool turnOffMotor10 = false;
bool turnOffMotor11 = false;

unsigned long currentMicros = 0;    // stores the value of micros() in each iteration of loop()

unsigned long previousMotor1Micros = 0; // will store last time the pin states were updated
unsigned long previousMotor2Micros = 0;
unsigned long previousMotor3Micros = 0; 
unsigned long previousMotor4Micros = 0;
unsigned long previousMotor5Micros = 0;
unsigned long previousMotor6Micros = 0; 
unsigned long previousMotor7Micros = 0;
unsigned long previousMotor8Micros = 0;
unsigned long previousMotor9Micros = 0; 
unsigned long previousMotor10Micros = 0; 
unsigned long previousMotor11Micros = 0;

unsigned long previousSerialMicros = 0;

byte serialReadBuffer[2];

//========

void setup() {
  Serial.begin(9600);

  pinMode(motor1Pin, OUTPUT);
  pinMode(motor2Pin, OUTPUT);
  pinMode(motor3Pin, OUTPUT);
  pinMode(motor4Pin, OUTPUT);
  pinMode(motor5Pin, OUTPUT);
  pinMode(motor6Pin, OUTPUT);
  pinMode(motor7Pin, OUTPUT);
  pinMode(motor8Pin, OUTPUT);
  pinMode(motor9Pin, OUTPUT);
  pinMode(motor10Pin, OUTPUT);
  pinMode(motor11Pin, OUTPUT);
}

void loop() {
  // Notice that none of the action happens in loop() apart from reading millis()
  // it just calls the functions that have the action code
  
  currentMicros = micros();   // capture the latest value of micros()
                              // this is equivalent to noting the time from a clock
                              // use the same time for all motors to keep them synchronized
  pollSerial();
  
  updateMotor1State();
  updateMotor2State();
  updateMotor3State();
  updateMotor4State();
  updateMotor5State();
  updateMotor6State();
  updateMotor7State();
  updateMotor8State();
  updateMotor9State();
  updateMotor10State();
  updateMotor11State();
  
  switchMotorPinStates();
}

void pollSerial()
{
  if (currentMicros - previousSerialMicros >= serialPollInterval) {
    while(Serial.available()) //TODO: try if(Serial.available())
    {
      Serial.readBytesUntil(BORDER_CHAR, serialReadBuffer, 2);
      
      bool turnOff = serialReadBuffer[TONE] == 1;
      
      unsigned long duration = map(serialReadBuffer[TONE], 0, 127, maxMotorSpeed, minMotorSpeed);  
      
      switch(serialReadBuffer[MOTOR_NUMBER])
      {
        case 1:
        {
          turnOffMotor1 = turnOff;
          motor1Duration = duration; //map(serialReadBuffer[TONE], 0, 127, maxMotorSpeed, minMotorSpeed); //map MIDI CC 0 - 127 to fan frequency 50 - 500
          break;
        }
        case 2:
        {
          turnOffMotor2 = turnOff;
          motor2Duration = duration; //map(serialReadBuffer[TONE], 0, 127, maxMotorSpeed, minMotorSpeed); //map MIDI CC 0 - 127 to fan frequency 50 - 500
          break;
        }
        case 3:
        {
          turnOffMotor3 = turnOff;
          motor3Duration = duration; //map(serialReadBuffer[TONE], 0, 127, maxMotorSpeed, minMotorSpeed); //map MIDI CC 0 - 127 to fan frequency 50 - 500
          break;
        }
        case 4:
        {
          turnOffMotor4 = turnOff;
          motor4Duration = duration;
          break;
        }
        case 5:
        {
          turnOffMotor5 = turnOff;
          motor5Duration = duration;
          break;
        }
        case 6:
        {
          turnOffMotor6 = turnOff;
          motor6Duration = duration;
          break;
        }
        case 7:
        {
          turnOffMotor7 = turnOff;
          motor7Duration = duration;
          break;
        }
        case 8:
        {
          turnOffMotor8 = turnOff;
          motor8Duration = duration;
          break;
        }
        case 9:
        {
          turnOffMotor9 = turnOff;
          motor9Duration = duration;
          break;
        }
        case 10:
        {
          turnOffMotor10 = turnOff;
          motor10Duration = duration;
          break;
        }
        case 11:
        {
          turnOffMotor11 = turnOff;
          motor11Duration = duration;
          break;
        }
      }
    }
    
    previousSerialMicros += serialPollInterval;
  }
}

void updateMotor1State() {
if(turnOffMotor1)
{
  motor1State = LOW;
  return;
}

 if (motor1State == LOW) {
   if (currentMicros - previousMotor1Micros >= motor1Duration) {
      motor1State = HIGH;
      previousMotor1Micros += motor1Duration;
   }
 }
 else {
   if (currentMicros - previousMotor1Micros >= motor1Duration) {
      motor1State = LOW;
      previousMotor1Micros += motor1Duration;
   } 
 }
}

void updateMotor2State() {
 if(turnOffMotor2)
 {
  motor2State = LOW;
  return;
 }
  if (currentMicros - previousMotor2Micros >= motor2Duration) {
    if (motor2State == LOW) {
      motor2State = HIGH;
    }
    else {
      motor2State = LOW;
    }
    previousMotor2Micros += motor2Duration;
  }  
}


void updateMotor3State() {
 if(turnOffMotor3)
 {
  motor3State = LOW;
  return;
 }
  if (currentMicros - previousMotor3Micros >= motor3Duration) {
    if (motor3State == LOW) {
      motor3State = HIGH;
    }
    else {
      motor3State = LOW;
    }
    previousMotor3Micros += motor3Duration;
  }  
}

void updateMotor4State() {
 if(turnOffMotor4)
 {
  motor4State = LOW;
  return;
 }
  if (currentMicros - previousMotor4Micros >= motor4Duration) {
    if (motor4State == LOW) {
      motor4State = HIGH;
    }
    else {
      motor4State = LOW;
    }
    previousMotor4Micros += motor4Duration;
  }  
}

void updateMotor5State() {
 if(turnOffMotor5)
 {
  motor5State = LOW;
  return;
 }
  if (currentMicros - previousMotor5Micros >= motor5Duration) {
    if (motor5State == LOW) {
      motor5State = HIGH;
    }
    else {
      motor5State = LOW;
    }
    previousMotor5Micros += motor5Duration;
  }  
}

void updateMotor6State() {
 if(turnOffMotor6)
 {
  motor6State = LOW;
  return;
 }
  if (currentMicros - previousMotor6Micros >= motor6Duration) {
    if (motor6State == LOW) {
      motor6State = HIGH;
    }
    else {
      motor6State = LOW;
    }
    previousMotor6Micros += motor6Duration;
  }  
}

void updateMotor7State() {
 if(turnOffMotor7)
 {
  motor7State = LOW;
  return;
 }
  if (currentMicros - previousMotor7Micros >= motor7Duration) {
    if (motor7State == LOW) {
      motor7State = HIGH;
    }
    else {
      motor7State = LOW;
    }
    previousMotor7Micros += motor7Duration;
  }  
}

void updateMotor8State() {
 if(turnOffMotor8)
 {
  motor8State = LOW;
  return;
 }
  if (currentMicros - previousMotor8Micros >= motor8Duration) {
    if (motor8State == LOW) {
      motor8State = HIGH;
    }
    else {
      motor8State = LOW;
    }
    previousMotor8Micros += motor8Duration;
  }  
}

void updateMotor9State() {
 if(turnOffMotor9)
 {
  motor9State = LOW;
  return;
 }
  if (currentMicros - previousMotor9Micros >= motor9Duration) {
    if (motor9State == LOW) {
      motor9State = HIGH;
    }
    else {
      motor9State = LOW;
    }
    previousMotor9Micros += motor9Duration;
  }  
}

void updateMotor10State() {
 if(turnOffMotor10)
 {
  motor10State = LOW;
  return;
 }
  if (currentMicros - previousMotor10Micros >= motor10Duration) {
    if (motor10State == LOW) {
      motor10State = HIGH;
    }
    else {
      motor10State = LOW;
    }
    previousMotor10Micros += motor10Duration;
  }  
}

void updateMotor11State() {
 if(turnOffMotor11)
 {
  motor11State = LOW;
  return;
 }
  if (currentMicros - previousMotor11Micros >= motor11Duration) {
    if (motor11State == LOW) {
      motor11State = HIGH;
    }
    else {
      motor11State = LOW;
    }
    previousMotor11Micros += motor11Duration;
  }  
}

void switchMotorPinStates() {
 // this is the code that actually switches pins on and off
 
 digitalWrite(motor1Pin, motor1State);
 digitalWrite(motor2Pin, motor2State);
 digitalWrite(motor3Pin, motor3State);
 digitalWrite(motor4Pin, motor4State);
 digitalWrite(motor5Pin, motor5State);
 digitalWrite(motor6Pin, motor6State);
 digitalWrite(motor7Pin, motor7State);
 digitalWrite(motor8Pin, motor8State);
 digitalWrite(motor9Pin, motor9State);
 digitalWrite(motor10Pin, motor10State);
 digitalWrite(motor11Pin, motor11State);
}

