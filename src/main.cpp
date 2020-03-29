#include <Arduino.h>
#include <WiFi.h>
#include "FireBaseESP32.h"

#define FIREBASE_HOST "https://hyperinfinitycube.firebaseio.com/"
#define FIREBASE_AUTH "AZ7ia8jJRJXjh9U9BjE0V1tFwn7Oclq5KUSaf52a"

const char* ssid = "FRITZ!Box WLAN 3370";
const char* password = "0045939574773306";

FirebaseData firebaseData;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid);

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());  

  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  
  }

void loop() {
  if (Firebase.getString(firebaseData, "/power")) {

    //if (firebaseData.dataType() == "string"){
      Serial.println(firebaseData.stringData());
    //}

  } else {
    Serial.println(firebaseData.errorReason());
  } 
  delay(1000);
}