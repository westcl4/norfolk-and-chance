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
  //Wire.begin(); 
  mlx.begin();  
  lcd.begin(16, 2);                 //tell the lcd library that we are using a display that is 16 characters wide and 2 characters high
  lcd.clear();                      //clear the display
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
  if (mlx.readObjectTempC() >= 35) {
     red();
     tone(buzzerPin, 272);
     lcd.print("DANGER EVACUATE ");
     lcd.setCursor(0, 1);   
     lcd.print("DANGER EVACUATE ");
     Wire.beginTransmission(9); // transmit to device #9
     Wire.write(x);              // sends x 
     Wire.endTransmission();
  }
  else {
        green();
        lcd.print("Tempertaure Safe"); 
        noTone(buzzerPin);
  }
//  Serial.println(mlx.readAmbientTempC());
 // Serial.println(mlx.readObjectTempC());
  delay(500);
}

void red() {

  //set the LED pins to values that make red
  analogWrite(RedPin, 100);
  analogWrite(GreenPin, 0);
  analogWrite(BluePin, 0);
}

void green() {

  //set the LED pins to values that make red
  analogWrite(RedPin, 0);
  analogWrite(GreenPin, 100);
  analogWrite(BluePin, 0);
}
