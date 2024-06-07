
 //FINAL YEAR PROJECT WORK

#include <Wire.h>
#include <LiquidCrystal.h>
#include<SoftwareSerial.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


const int trigPin = 6; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 7; // Echo Pin of Ultrasonic Sensor
long duration;
int OilLevel;
const int Relay_PIN = 7;




int delayTime = 700;

int EarthCurrent;
float SensorReadEarth;
float sensitivity = 0.185;
int temp;
float TempSensorPin = A0;
float vout;
//Measuring Current Using ACS712
const int Sensor_Pin = A0; //Connect current sensor with A0 of Arduino
int sensitivity = 100; // use 100 for 20A Module and 66 for 30A Module
int offsetvoltage = 2500; 


void setup() {
  // put your setup code here, to run once:
pinMode(TempSensorPin,INPUT);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
 pinMode(Relay_PIN, OUTPUT);  // Set the pin as OUTPUT 
 Serial.begin(9600);
 delay(100);

Serial.println(" REMOTE TRANSFORMER MONITORING");  
lcd.begin(20,4);
lcd.print("PROJECT WORK");
lcd.setCursor(2,1);
lcd.print("REMOTE");
lcd.setCursor(9,1);
lcd.print("MONITORING");
lcd.setCursor(4,2);
lcd.print("TRANSFORMER");
delay (delayTime);
lcd.clear();

}

void loop() {



//temperature//
vout = analogRead(TempSensorPin);
vout = (vout * 500) / 1023;
temp = vout;


//EARTH CURRENT//
SensorReadEarth = analogRead(A1)*(5.0 / 1023.0);     //We read the sensor output  
EarthCurrent = (SensorReadEarth - 2.5)/sensitivity;   //Calculate the current value for earth


// SENSING OIL LEVEL//
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
OilLevel = duration * 0.034 / 2;


//LCD PRINTING//
  
lcd.setCursor(0,0);
lcd.print("Temperature:");
lcd.setCursor(12,0);
lcd.print(temp);
lcd.setCursor(15,0);
lcd.print("C");

lcd.setCursor(0,1);
lcd.print("Oil Level:");
lcd.setCursor(10,1);
lcd.print(OilLevel);
lcd.setCursor(14,1);
lcd.print("CM");

lcd.setCursor(0, 2);
lcd.print("Earth Current:");
lcd.setCursor(14, 2);
lcd.print(EarthCurrent,2);
lcd.setCursor(16, 2);
lcd.print("A");
delay(600);

condition();

}


//CONDITIONS
void condition()
{
  if (temp > 75)
{
lcd_tempPrint();

 delay(300);
  
  }
if (OilLevel > 800)
{
 lcd_oilLevelFULLPrint();

 
 delay(1000);
  }else if (OilLevel < 300)
{lcd_oilLevelLOWPrint();

 delay(300);
  }

   
}


// LCD PRINTING CONDITION//

void lcd_oilLevelFULLPrint()
{
lcd.clear();
lcd.setCursor(1,1);
lcd.clear();                                  //if condition temp for it to print.
lcd.print("OIL TANK FULL");  
 
}

void lcd_oilLevelLOWPrint()
{
lcd.clear();
lcd.setCursor(0,2);
lcd.clear();                                  //if condition temp for it to print.
lcd.print("OIL LEVEL LOW");  

}



void lcd_tempPrint()
{
lcd.clear();
lcd.setCursor(0,0);
lcd.clear();                                  //if condition temp for it to print.
lcd.print("HIGH TEMPERATURE");   
  
}




 
