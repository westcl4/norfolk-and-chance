
#include <LiquidCrystal.h>          //the liquid crystal library contains commands for printing to the display
#include <Wire.h>                   //the Wire library allows communication with I2C
#include <Adafruit_MLX90614.h>      //the library to get methods to work with the IR temp sensor

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);   // tell the RedBoard what pins are connected to the display

int RedPin = 5;                           //Pins for the RGB light
int GreenPin = 6;
int BluePin = 7;
int buzzerPin = 4;                       //Pin for the buzzer
int x = 0;                               //Initialises the varaible for communication with the slave arduino 


void setup() {                           //Constructor that instantiates objects of the Wire, Liquid crystal and Adafruit libraries
  Wire.begin(); 
  mlx.begin();  
  lcd.begin(16, 2);                 
  lcd.clear();                     
  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  green();                              //Sets the RGB light to green on startup
}

void loop() {         
  if (mlx.readObjectTempC() >= 35 || mlx.readAmbientTempC() >= 35 ) {  //Checks if Object or Ambient temp is above 35 degree C. Source for the library and how to use its methods https://github.com/adafruit/Adafruit-MLX90614-Library/blob/master/Adafruit_MLX90614.cpp 
     red();                                                            //Sets light to red
     tone(buzzerPin, 272);                                             //Sounds the buzzer
     lcd.setCursor(0,0);
     lcd.print("DANGER EVACUATE!");                                    //Prints to screen warning message
     lcd.setCursor(0,1);
     lcd.print("DANGER EVACUATE!");
     Wire.beginTransmission(9);                                        //Sends byte to slave arduino signalling it should stop
     x = 1;
     Wire.write(x);             
     Wire.endTransmission();
  }
  else {
        green();                                                       //Sets light to green
        lcd.setCursor(0,0);
        lcd.print("Tempertaure Safe");                                 //Prints to screen safe message
        lcd.setCursor(0,1);
        lcd.print("Tempertaure Safe"); 
        noTone(buzzerPin);
        Wire.beginTransmission(9);                                     //Sends byte to slave arduino signalling to start
        x = 0;
        Wire.write(x);             
        Wire.endTransmission();
  }
}

void red() {                                                           //Method to set light to red
  analogWrite(RedPin, 100);
  analogWrite(GreenPin, 0);
  analogWrite(BluePin, 0);
}

void green() {                                                        //Method to set light to green
  analogWrite(RedPin, 0);
  analogWrite(GreenPin, 100);
  analogWrite(BluePin, 0);
}
