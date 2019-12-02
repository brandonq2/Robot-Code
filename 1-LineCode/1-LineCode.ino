// Libraries Needed
#include <Servo.h>
#include <Wire.h>

// Motor Variables
const int rightMotor = 6;
const int leftMotor = 5;
const int rightRelay = 4;
const int leftRelay = 7;

// Line Sensing Array
int* raw = new int[8];
int* data;

// Variable to keep track of which direction you're going
int EastWest = 0; // Two consecutive turns in the same direction is a change in direction
int NorthSouth = 0;

void setup() {
  // Basic setup
  Serial.begin(9600);
  Wire.begin();

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
  data = rawarray(); // Data is a pointer to the array address

  if (data[0] <= 100 && data[1] <= 100 && data[2] <= 100){ // A wide line was detected, meaning sharp turn
    sharpTurnLeft();
  }
  else if (data[5] <= 100 && data[6] <= 100 && data[7] <= 100){
    sharpTurnRight();
  }
  else if (data[0] <= 100|| data[1] <= 100 || data[2] <= 100){
    slightTurnLeft();
  }
  else if(data[3] <= 100 || data[4] <= 100){
    moveForward();
  }
  else if(data[5] <= 100 || data[6] <= 100 || data[7] <= 100){
    slightTurnRight();
  }
  else{
    sharpTurnRight();
    Serial.println("HERE");
    slightTurnRight();
    slightTurnRight();
    moveForward();
    delay (500);
    backup();
    delay(200);
    sharpTurnLeft();
  }

}

// Line Sensing Function
int* rawarray(){
  Wire.requestFrom(9, 16);
  for (int i=0; i <= 7; i++) raw[i] = Wire.read() << 8 | Wire.read();
  return raw;
}

void moveForward(){
  digitalWrite(rightMotor, HIGH); // Robot starts off not moving
  digitalWrite(leftMotor, HIGH);
  digitalWrite(rightRelay, HIGH); // One is opposite because the motor is flipped
  digitalWrite(leftRelay, LOW); 
}

void backup(){
  digitalWrite(rightMotor, HIGH); // Robot starts off not moving
  digitalWrite(leftMotor, HIGH);
  digitalWrite(rightRelay, LOW); // One is opposite because the motor is flipped
  digitalWrite(leftRelay, HIGH); 
}
// Line Turning Functions
void slightTurnLeft(){
  digitalWrite(leftRelay, HIGH);
  delay(80);
  digitalWrite(leftRelay, LOW);
}

void slightTurnRight(){
  digitalWrite(rightRelay, LOW);
  delay(80);
  digitalWrite(rightRelay, HIGH);
}

void sharpTurnLeft(){
  delay(300);
  digitalWrite(leftRelay, HIGH);
  delay(400);
  digitalWrite(leftRelay, LOW);
}

void sharpTurnRight(){
  delay(300);
  digitalWrite(rightRelay, LOW);
  delay(400);
  digitalWrite(rightRelay, HIGH);
}
