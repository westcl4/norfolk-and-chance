#include <Wire.h>

void setup() {
  Wire.begin(9);                 // join i2c bus with address #4
  Wire.onReceive(receiveEvent); 
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    delay(100);
}

void receiveEvent()
{
    digitalWrite(13, HIGH);
    
}
