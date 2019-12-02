#include <Wire.h>
#define uchar unsigned char
uchar t;
//void send_data(short a1,short b1,short c1,short d1,short e1,short f1);
uchar data[16];
void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  t = 0;
}
void loop()
{
  int *data = rawarray();
  for (int i=0; i <= 7; i++){
    Serial.print("\t"); 
    Serial.print("Data[");
    Serial.print(i);
    Serial.print("]");
    Serial.println( *(data +i) );
  }
  Serial.println("----------------------------------------");
  delay(1000);

  if (data[0] <= 100 || data[1] <= 100 || data[2] <= 100){
    left();
  }
  if(data[6] <= 100 || data[7] <= 100 || data[5] <= 100){
    right();
  }
  
}

void left(){
  Serial.println("LEFT");
}
void right(){
  Serial.println("RIGHT");
}

int * rawarray(){
int* raw = new int[8];
  Wire.requestFrom(9, 16);
  for (int i=0; i <= 7; i++) raw[i] = Wire.read() << 8 | Wire.read();
  return raw;
}
