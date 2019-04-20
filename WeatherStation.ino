#include "DHT.h"
#include <Adafruit_BMP085.h>
#include <Wire.h>
#include <LiquidCrystal.h>

#define DHTPIN 7 // Pin where DHT was connected
#define DHTTYPE DHT11 // DHT 11

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 

DHT dht(DHTPIN, DHTTYPE);

float t, v, ldrValue, bmp, temperature, humidity;
t = v = ldrValue = bmp = temperature = humidity = 0;
Adafruit_BMP085 bmp180;

int temp; //Variable temp to write on the LCD
int LDR = 1;
int sensorPin = A0;
int readValue = 0;

void setup(){
    dht.begin();
    pinMode(LDR, INPUT);
    Serial.begin(9600); 
    lcd.begin(16, 2);
    lcd.setCursor(0, 0); 
    lcd.print("Weather");
    lcd.setCursor(0, 1);
    lcd.print("Station");
    delay(3000);
    lcd.clear();
    Serial.begin(9600);
}

void loop(){
    float h = dht.readHumidity();
    readValue = analogRead(sensorPin);
    t = (readValue * 0.00488);
    t = t * 100;
    v = analogRead(LDR);
    ldrValue=(v*0.004883);//Calibration of the sensor
    humidity=(h/0.568515)-(24.1289/0.568515); //Calibration of the sensor
    bmp=bmp180.readPressure();
    temperature=(t/0.984332)-(0.4039/0.984332);//Calibration of the sensor

    lcd.setCursor(0, 0);
    lcd.print("Pressure: ");
    lcd.setCursor(0, 1);
    lcd.println(bmp);
    lcd.println(" Pa");
    delay (3000);
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Luminosity: ");
    lcd.setCursor(0, 1);
    lcd.println(ldrValue);
    lcd.println(" V");
    delay (3000);
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Temperature : ");
    lcd.setCursor(0, 1);
    lcd.println(temperature);
    lcd.println(" C");
    delay (3000);
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Current humidity: ");
    lcd.setCursor(0, 1);
    lcd.println(humidity);
    lcd.println(" %");
    delay (3000);
    lcd.clear();
    delay (2000);
}
