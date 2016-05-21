#include <SPI.h>
#include <Wire.h>
#include <nRF24L01p.h>
#include <Adafruit_BMP085.h>
#include <SoftwareSerial.h>
#include "DHT.h"

#define DHTPIN 3
#define DHTTYPE DHT22

SoftwareSerial portOne(5, 4);//tx,rx
Adafruit_BMP085 bmp;
DHT dht(DHTPIN, DHTTYPE);
nRF24L01p nRF24(7, 6);

byte readSensor = 2;
String mode= "";
String inString1 = "";
String inString2 = "";
String tmpData1 = "";
String tmpData2 = "";
String allData = "";

void setup(){
  delay(150);
  Serial.begin(9600);
  while(!Serial){
    ;
  }
  bmp.begin();
  dht.begin();
  portOne.begin(9600);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  nRF24.channel(94);
  nRF24.RXaddress("Raddr4");
  nRF24.TXaddress("Taddr4");
  nRF24.init();
 }

void loop(){
  uint32_t now = 0;
  static uint32_t last_t;
  now = millis();
  if((now-last_t) > 1000){
    last_t = now;
    switch (readSensor){
      case 1:
        portOne.println(";");
        //portOne.listen();
        while (portOne.available() > 0){
          char inByte1 = portOne.read();
          inString1 += inByte1;
          Serial.print(inByte1);
          if(inByte1 == '\n'){
            tmpData1 = inString1;
            inString1 = "";
            readSensor = 2;
          }
        }
       break;
       case 2:       
         nRF24.txPL(mode);
         nRF24.send(FAST);
         if(nRF24.available()){
          tmpData2 ="";
          nRF24.read();
          nRF24.rxPL(tmpData2);          
          readSensor = 2;
         }
       break; 
       case 3:
        printData();
        readSensor = 1;
       break;
     }
   }
}


void printData(){
  allData = String(bmp.readPressure());
  allData += ",";
  allData += String(dht.readTemperature());
  allData += ",";
  allData += String(dht.readHumidity());
  allData += ",";
  allData += tmpData1;
  allData += ",";
  allData += tmpData2;
  Serial.println(allData);
}


void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
   
    if (inChar == '0') {
      mode = "0";
    }
    if(inChar == '1'){
      mode = "1";
    }
    if (inChar == '2'){
      mode = "2";      
    }
    if(inChar == '3'){
      mode = "3";
    }
    if(inChar == '4'){
      mode = "4";
    }
    if(inChar == '5'){
      mode = "5";  
    }
    if(inChar == '6'){
      mode = "6";
    }
    if(inChar == 'a'){
      mode = "a";
      printData();
    }
    if(inChar == 'b'){
      mode = "b";
      printData();
    }
    if(inChar == 'c'){
      mode = "c";
      printData();
    }
    if(inChar == 'd'){
      mode = "d";
      printData();
    }
    if(inChar == 'e'){
      mode = "e";
      printData();
    }
  }    
}

