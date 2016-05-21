#include <SPI.h>
#include <Wire.h>
#include <nRF24L01p.h>
#include <Adafruit_BMP085.h>
#include <SoftwareSerial.h>
#include "DHT.h"

#define DHTPIN 3
#define DHTTYPE DHT22


Adafruit_BMP085 bmp;
DHT dht(DHTPIN, DHTTYPE);

String inString1 = "";
String inString2 = "";
String tmpData1 = "";
String tmpData2 = "";
String allData = "";
String lastHumi = "60.00";
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup(){
  Serial.begin(9600);
  while(!Serial){
    ;
  }
  bmp.begin();
  dht.begin();
 
  
}

void loop(){
  uint32_t now = 0;
  static uint32_t last_t;
  now = millis();
  if((now-last_t) > 500){
    last_t = now;
    
  allData = String(bmp.readPressure());
  allData += ",";
  allData += String(dht.readTemperature());
  allData += ",";
  String sDht = String(dht.readHumidity());
  if(sDht.length() > 4){
    allData += sDht;
    lastHumi = sDht;  
  }else{
    allData += lastHumi;
  } 
  }
  if(stringComplete == true){
    Serial.println(allData);
    stringComplete = false;
  }

}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
      
    }
  }    
}

