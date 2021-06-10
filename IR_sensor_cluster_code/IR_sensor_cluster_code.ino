/*
  SparkFun Inventor’s Kit
  Circuit 4A-HelloWorld

  The LCD will display the words "Hello World" and show how many seconds have passed since
  the RedBoard was last reset.

  This sketch was written by SparkFun Electronics, with lots of help from the Arduino community.
  This code is completely free for any use.

  View circuit diagram and instructions at: https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v40
  Download drawings and code at: https://github.com/sparkfun/SIK-Guide-Code
*/

#include <LiquidCrystal.h>          //the liquid crystal library contains commands for printing to the display
#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);   // tell the RedBoard what pins are connected to the display
int RedPin = 5;
int GreenPin = 6;
int BluePin = 7;
int buzzerPin = 4;
byte x = 0;

void setup() {
  Wire.begin(); 
  mlx.begin();  
  lcd.begin(16, 2);                 
  lcd.clear();                     
  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  lcd.setCursor(0, 0);             
  lcd.print("Tempertaure Safe"); 
  green();
  Serial.begin (9600);
}

void loop() {         
  if (mlx.readObjectTempC() >= 35 || mlx.readAmbientTempC >= 35 ) {
     red();
     tone(buzzerPin, 272);
     lcd.clear();
     lcd.print("DANGER EVACUATE ");
     Wire.beginTransmission(9); 
     Wire.write(x);             
     Wire.endTransmission();
  }
  else {
        green();
        lcd.clear();
        lcd.print("Tempertaure Safe"); 
        noTone(buzzerPin);
  }
}

void red() {
  analogWrite(RedPin, 100);
  analogWrite(GreenPin, 0);
  analogWrite(BluePin, 0);
}

void green() {
  analogWrite(RedPin, 0);
  analogWrite(GreenPin, 100);
  analogWrite(BluePin, 0);
}
