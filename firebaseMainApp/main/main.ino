/*@Author: EPCB TECH*/
/*@Date: 2020*/
/*@Description: Counter Proximity Sensor with Firebase Realtime Server */

/*Note: Only authorized accounts can access our realtime database */
/*Contact: epcbtech@gmail.com*/
/*Server Address:https://vvcisensorhost.firebaseio.com */

#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <DNSServer.h>

#define proximitySensorPin D2 //Sensor Pin
#define resetPin           D1 //Button Reset counter pin

const char* ssid        = "SSID";
const char* password    = "password";

int sensorState         = 0;
int sensorPushCounter   = 0;
int lastSensorState     = 0;

int resetState          = 0;

FirebaseData firebaseData;
WiFiManager  wifiManager;

void EPCBsign();
void connectWiFiAuto();
void connectWiFiHandle();
void connectFirebaseServer();
void resetCounter(int &resetState);

void setup(){
  Serial.begin(9600);
  EPCBsign();
  connectWiFiAuto();
  connectFirebaseServer();
  pinMode(proximitySensorPin, INPUT_PULLUP);
  pinMode(resetPin, INPUT_PULLUP);
}

void loop(){
  sensorState = digitalRead(proximitySensorPin);
  resetState  = digitalRead(resetPin);
  
  if(sensorState != lastSensorState){
    if(sensorState == HIGH){
      sensorPushCounter++;
      Serial.println("Counter: ");
      Serial.println(sensorPushCounter - 1);
      Firebase.setInt(firebaseData, "/count", sensorPushCounter - 1);
    }
  }
  resetCounter(resetState);
  lastSensorState = sensorState;
}

void connectWiFiAuto(){
  wifiManager.autoConnect("AutoConnectAP");
  Serial.println("Connected");
}

void connectWiFihandle(){
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(200);
    Serial.print(".");
  }
  Serial.print("......");
  Serial.print("WiFi Connected.....IP Address:");
  Serial.println(WiFi.localIP());
}

void connectFirebaseServer(){
  Firebase.begin("https://vvcisensorhost.firebaseio.com/", "BOxodhdlCVfhZeIX7gaUP3knd197yoYm8BkKqtVf");
  Serial.println("Firebase Connected!");
}

void resetCounter(int &resetState){
   if (resetState == LOW){
    sensorPushCounter = 0;
    Serial.println("Reset Counter...");
    Firebase.setInt(firebaseData, "/count", sensorPushCounter);
    sensorState     = 0;
    lastSensorState = 0;
  }
}

void EPCBsign(void) {
  Serial.printf("==========================\n");
  Serial.printf("|| EPCBTechEPCBTechEPCB ||\n");
  Serial.printf("|| P                  T ||\n");
  Serial.printf("|| C      .*.         e ||\n");
  Serial.printf("|| B      * *  .*.    c ||\n");
  Serial.printf("|| T***.  * *  * `****h ||\n");
  Serial.printf("|| e   `**' *  *      E ||\n");
  Serial.printf("|| c        `**'      P ||\n");
  Serial.printf("|| h                  C ||\n");
  Serial.printf("|| EPCBTechEPCBTechEPCB ||\n");
  Serial.printf("==========================\n");
}
