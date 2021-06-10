
#include <LiquidCrystal.h>          //the liquid crystal library contains commands for printing to the display
#include <Wire.h>                   //the Wire library allows communication with I2C
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);   // tell the RedBoard what pins are connected to the display
int RedPin = 5;
int GreenPin = 6;
int BluePin = 7;
int buzzerPin = 4;
int x = 0;

void setup() {
  Wire.begin(); 
  mlx.begin();  
  lcd.begin(16, 2);                 
  lcd.clear();                     
  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  green();
  Serial.begin (9600);
}

void loop() {         
  if (mlx.readObjectTempC() >= 35 || mlx.readAmbientTempC() >= 35 ) {
     red();
     tone(buzzerPin, 272);
     lcd.setCursor(0,0);
     lcd.print("DANGER EVACUATE!");
     lcd.setCursor(0,1);
     lcd.print("DANGER EVACUATE!");
     Wire.beginTransmission(9); 
     x = 1;
     Wire.write(x);             
     Wire.endTransmission();
  }
  else {
        green();
        lcd.setCursor(0,0);
        lcd.print("Tempertaure Safe");
        lcd.setCursor(0,1);
        lcd.print("Tempertaure Safe"); 
        
        noTone(buzzerPin);
        Wire.beginTransmission(9); 
        x = 0;
        Wire.write(x);             
        Wire.endTransmission();
  }
}
void receiveEvent(int bytes) {
  x = Wire.read();    // read one character from the I2C
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
