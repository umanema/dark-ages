//------- CONSTANTS

//TODO: REFAC THIS CODE!!!

const int motorPin[11] = {2,3,4,5,6,
                          7,8,9,10,11};

const unsigned long maxMotorSpeed = 10000;
const unsigned int minMotorSpeed = 0;

const long doNotRotate = 500000;

//------- VARIABLES

byte motorState[11] = {LOW,LOW,LOW,LOW,LOW,
                       LOW,LOW,LOW,LOW,LOW,LOW}; // LOW = off

unsigned long motorLifetime[11] = {0,0,0,0,0,
                                   0,0,0,0,0,0}; //microsec

unsigned long motorDuration[11] = {100,100,100,100,100,
                                   100,100,100,100,100,100}; //microsec

bool turnOffMotor[11] = {false,false,false,false,false,
                         false,false,false,false,false,false};

unsigned long currentMicros = 0;    // stores the value of micros() in each iteration of loop()
unsigned long currentMillis = 0;    // stores the value of millis() in each iteration of loop()

unsigned long previousMotorMicros[11] = {0,0,0,0,0,
                                         0,0,0,0,0,0};// will store last time the pin states were updated

unsigned long elapsedMotorMillis[11] = {0,0,0,0,0,
                                         0,0,0,0,0,0};
unsigned long previousSerialMicros = 0;

//========

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 11; i++) {
    pinMode(motorPin[i], OUTPUT);
  }

}

void loop() {
  // Notice that none of the action happens in loop() apart from reading millis()
  // it just calls the functions that have the action code
  
  currentMicros = micros();   // capture the latest value of micros()
                              // this is equivalent to noting the time from a clock
                              // use the same time for all motors to keep them synchronized

  currentMillis = millis();
  
  switchMotorPinStates();
}

void driveMotor(int motorNumber) {
  motorLifetime[motorNumber] += elapsedMotorMillis[motorNumber] - currentMillis;
  elapsedMotorMillis[motorNumber] = currentMillis;
  if (motorLifetime[motorNumber] > 0) {
    if (currentMicros - previousMotorMicros[motorNumber] >= motorDuration[motorNumber]) {
      previousMotorMicros[motorNumber] += motorDuration[motorNumber];
      if (motorState[motorNumber] == LOW) {
        motorState[motorNumber] = HIGH;
      }
      else {
        motorState[motorNumber] = LOW;
      }
    }  
  } else {
    randomizeMotorLifetime(motorNumber);
  }
}

long randomizeMotorLifetime(int motorNumber)
{
  motorLifetime[motorNumber] = random(0, 100000);
  motorDuration[motorNumber] = random(minMotorSpeed, maxMotorSpeed);
}

void switchMotorPinStates() {
 // this is the code that actually switches pins on and off
  for (int i = 0; i < 11; i++) { 
    driveMotor(i);
    digitalWrite(motorPin[i], motorState[i]);
  }
}

void test() {
  //this is test regime when every motor is working
  for (int i = 0; i < 11; i++) { 
    driveMotor(i);
    digitalWrite(motorPin[i], HIGH);
  }
}

