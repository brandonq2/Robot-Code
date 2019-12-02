// Libraries Needed
#include <Servo.h>
#include <Wire.h>

// Motor Variables
const int rightMotor = 6;
const int leftMotor = 5;
const int rightRelay = 4;
const int leftRelay = 7;

// Flame Sensor Vairables
const int flameSensorLeft = A0;
const int flameSensorMid = A1;
const int flameSensorRight = A2;
int flameValueLeft = 0;
int flameValueMid = 0;
int flameValueRight = 0;

void setup() {
  // Basic setup
  Serial.begin(9600);

  // Motor pin modes and starting values
  pinMode(leftMotor, INPUT);
  pinMode(rightMotor, INPUT);
  pinMode(leftRelay, OUTPUT);
  pinMode(rightRelay, OUTPUT);

  digitalWrite(rightMotor, HIGH); // Robot starts off not moving
  digitalWrite(leftMotor, HIGH);
  digitalWrite(rightRelay, HIGH); // One is opposite because the motor is flipped
  digitalWrite(leftRelay, LOW); 
}

void loop() {
  flameValueLeft = analogRead(flameSensorLeft);
  flameValueMid = analogRead(flameSensorMid);
  flameValueRight = analogRead(flameSensorRight);
  Serial.println(flameValueLeft);

  if (flameValueLeft < 700 || flameValueMid < 700 || flameValueRight < 700){
    stopMotors();
  }
  else if(flameValueLeft < 850){
    slightTurnLeft();
    Serial.println("Left");
  }
  else if (flameValueRight < 850){
    slightTurnRight();
    Serial.println("Right");
  }
}

// Movement Functions
void slightTurnLeft(){
  digitalWrite(rightMotor, HIGH); // Robot starts off not moving
  digitalWrite(leftMotor, HIGH);
  digitalWrite(leftRelay, HIGH);
  delay(80);
  digitalWrite(leftRelay, LOW);
  //digitalWrite(rightMotor, LOW); // Robot starts off not moving
  //digitalWrite(leftMotor, LOW);
}

void slightTurnRight(){
  digitalWrite(rightMotor, HIGH); // Robot starts off not moving
  digitalWrite(leftMotor, HIGH);
  digitalWrite(rightRelay, LOW);
  delay(80);
  digitalWrite(rightRelay, HIGH);
  //digitalWrite(rightMotor, LOW); // Robot starts off not moving
  //digitalWrite(leftMotor, LOW);
}

void stopMotors(){
  digitalWrite(leftMotor, LOW);
  digitalWrite(rightMotor, LOW);
}
