// Libraries Needed
#include <Servo.h>
#include <Wire.h>

// Motor Variables
const int rightMotor = 1;
const int leftMotor = 2;
const int rightRelay = 3;
const int leftRelay = 4;

// Object Sensor Vairables
const int objTrig = 5;
const int objEcho = 6;
long duration;
int distance;


void setup() {
  // Basic setup
  Serial.begin(9600);

  // Object sensor setup
  pinMode(objTrig, OUTPUT);
  pinMode(objEcho, INPUT);

  // Motor pin modes and starting values
  pinMode(leftMotor, INPUT);
  pinMode(rightMotor, INPUT);
  pinMode(leftRelay, OUTPUT);
  pinMode(rightRelay, OUTPUT);

  digitalWrite(rightMotor, LOW); // Robot starts off not moving
  digitalWrite(leftMotor, LOW);
  digitalWrite(rightRelay, HIGH); // One is opposite because the motor is flipped
  digitalWrite(leftRelay, LOW); 
}

void loop() {
  int objValue = objCheck();

  if(objValue < 10){
    turnAround();
  }
}

// Object Detection Function
int objCheck(){ // Might be able to make this constant checking.
  digitalWrite(objTrig, HIGH);
  delayMicroseconds(30);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;
  return distance;
}

// Turning Functions
void turnAround(){
  digitalWrite(rightRelay, LOW);
  delay(900);
  digitalWrite(rightRelay, HIGH);
}
