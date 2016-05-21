#include <SPI.h>
#include <Wire.h>
#include <nRF24L01p.h>
#include <Adafruit_BMP085.h>
#include "DHT.h"

#define DHTPIN 3
#define DHTTYPE DHT22

Adafruit_BMP085 bmp;
DHT dht(DHTPIN, DHTTYPE);
nRF24L01p nRF24(10, 14);

byte readSensor = 0;
byte mode = 0;
String inString1 = "";
String inString2 = "";
String tmpData1 = "";
String tmpData2 = "";

void setup(){
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  delay(150);
  Serial.begin(9600);
  while(!Serial){
   ;
  }
  bmp.begin();
  dht.begin();
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  nRF24.channel(94);
  nRF24.RXaddress("Taddr4");
  nRF24.TXaddress("Raddr4");
  nRF24.init();
  
}

void loop(){

  if(nRF24.available()){
    tmpData2 ="";
    nRF24.read();
    nRF24.rxPL(tmpData2);
    Serial.println(tmpData2);
    printData();  
  }
  if(tmpData2 == "1"){
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);   
  }
  if(tmpData2 == "2"){
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
  }
  if(tmpData2 == "3"){
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);   
  }
  if(tmpData2 == "4"){
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
  }
  if(tmpData2 == "5"){
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);   
  }
  if(tmpData2 == "6"){
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
  }
  if(tmpData2 == "a"){
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
  }
  
  if(tmpData2 == "b"){
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(6, LOW);
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
  }
  if(tmpData2 == "c"){
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);   
  }
  if(tmpData2 == "d"){
    digitalWrite(7, HIGH); 
  }
  if(tmpData2 == "e"){
    digitalWrite(7, LOW);
  }
}


void printData(){
  tmpData1 += String(bmp.readPressure(), 2);
  tmpData1 += ",";
  tmpData1 += String(dht.readTemperature(), 2);
  tmpData1 += ",";
  tmpData1 += String(dht.readHumidity(), 2);
  nRF24.txPL(tmpData1);
  nRF24.send(FAST);
  tmpData1 = "";
}

