#include <Arduino.h>
#include <WiFi.h>
#include "FireBaseESP32.h"
#include <FastLED.h>

#define FIREBASE_HOST "https://hyperinfinitycube.firebaseio.com/"
#define FIREBASE_AUTH "AZ7ia8jJRJXjh9U9BjE0V1tFwn7Oclq5KUSaf52a"

#define NUM_LEDS 300

const char* ssid = "MirDochEgal";
const char* password = "93153805";

CRGBArray<NUM_LEDS> leds;
const int ledPin = 25;

FirebaseData firebaseData;
boolean power = false;
int solidColor = 0;

CRGB getRGBColorAtRoot(String root){
  int r,g,b;

  if (Firebase.getInt(firebaseData,root + "/r")){
      r = firebaseData.intData();
    } else {
      Serial.println(firebaseData.errorReason());
  }
  
  if (Firebase.getInt(firebaseData,root + "/g")){
      g = firebaseData.intData();
    } else {
      Serial.println(firebaseData.errorReason());
  }
  
  if (Firebase.getInt(firebaseData,root + "/b")){
      b = firebaseData.intData();
    } else {
      Serial.println(firebaseData.errorReason());
    }
  
  return CRGB(r,g,b);
}

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
  
  pinMode(ledPin,OUTPUT);
  FastLED.addLeds<WS2812B, ledPin, GRB>(leds, NUM_LEDS);

  }

void loop() {
  if (Firebase.getBool(firebaseData, "/power")) {

    power = firebaseData.boolData();

  } else {
    Serial.println(firebaseData.errorReason());
  } 
  

  if (power){
    leds.fill_solid(getRGBColorAtRoot("color"));
    FastLED.show();
  } else {
    leds.fill_solid(CRGB::Black);
    FastLED.show();
    Serial.println("power off");
  }
  delay(50);
}

