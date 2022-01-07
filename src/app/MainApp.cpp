//
// ESP LEDs App
//
// Hoani Bryson (github.com/hoani)
// Copyright (c) 2022 Hoani Bryson.
// License - MIT
//


#include "../led/strip.h"
#include "../led/adafruitLEDStrip/adafruitLEDStrip.h"

#include "../3rdParty/ArduinoJson/ArduinoJson.h"
#include <WiFi.h>
#include "../jsonBuffer/jsonBuffer.h"
#include "MainApp.h"

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        2

#define LED 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 120
#define MAXPIXELS 5

static Adafruit_NeoPixel adafruitPixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
LEDStrip *pixels = new AdafruitLEDStrip(adafruitPixels);



#define DELAYVAL 10 // Time (in milliseconds) to pause between pixels

const Color colorAqua = Color(50, 150, 150);
const Color colorRed = Color(250, 30, 30);
const Color colorIndigo = Color(20, 5, 60);
const Color colorNone = Color(0, 0, 0);

static Color onColor = colorAqua;

void handleWifi();
void pixelsUpdate(int i);
void wifiConnect();


WiFiServer server(8080);

void MainApp::setup() {
  delay(500);
  adafruitPixels.begin(); 
  Serial.begin(115200);
  Serial.println();

  wifiConnect();

  pixels->clear(); // Set all pixel colors to 'off'
  int i = 0;
  
  while(true) {
    handleWifi();
    delay(DELAYVAL);
    pixelsUpdate(i);
    pixels->show();
    i = (i + 1) % (NUMPIXELS + MAXPIXELS);
  }
}

void MainApp::loop() {}

void handleWifi() {
  static WiFiClient c;
  static JSONBuffer<256> b;
  if (!c) {
    c = server.available();
    if (c) {
      if (c.connected()) {
        Serial.println("connected to client");
        c.write("hello from esp");
      }
    }
  } else {
    if (c.available()) {
      
      while (c.available()) {
        b.update(c);
        if (b.done()) {
          String s = b.getString();
          Serial.println("Received `" + s +"`");
          DynamicJsonDocument doc(1024);
          deserializeJson(doc, s);
          if (doc.containsKey("color")) {
            const char* color = doc["color"];
            if (String(color) == "red") {
              onColor = colorRed;
            } else if (String(color) == "aqua") {
              onColor = colorAqua;
            } else if (String(color) == "off") {
              onColor = colorNone;
            }
          }
        }
        b = JSONBuffer<256>();
      }
    }
  }
}

void pixelsUpdate(int i) {
  int lowPixel = i - MAXPIXELS;
  
  if (i < NUMPIXELS) {
    pixels->set(i, onColor);
  } 
  if (lowPixel >= 0) {
    pixels->set(lowPixel, colorIndigo);
  }
}

void wifiConnect() {
  WiFi.begin("Leetware", "1337ware");

  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  server.begin();
  
  Serial.print("Connected to ");
  Serial.print(WiFi.SSID());
  Serial.print("\tIP Addr:");
  Serial.print(WiFi.localIP());
  Serial.print("\tMacAddr:");
  Serial.println(WiFi.macAddress());
}
