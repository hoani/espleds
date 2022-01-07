//
// ESP LEDs App
//
// Hoani Bryson (github.com/hoani)
// Copyright (c) 2022 Hoani Bryson.
// License - MIT
//


#include "../3rdParty/Adafruit_NeoPixel/Adafruit_NeoPixel.h"
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

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 10 // Time (in milliseconds) to pause between pixels

const uint32_t colorAqua = pixels.Color(50, 150, 150);
const uint32_t colorRed = pixels.Color(250, 30, 30);
const uint32_t colorIndigo = pixels.Color(20, 5, 60);
const uint32_t colorNone = 0;

static uint32_t onColor = colorAqua;

void handleWifi();
void pixelsUpdate(int i);
void wifiConnect();


WiFiServer server(8080);

void MainApp::setup() {
  delay(500);
  pixels.begin(); 
  Serial.begin(115200);
  Serial.println();

  wifiConnect();

  pixels.clear(); // Set all pixel colors to 'off'
  int i = 0;
  
  while(true) {
    handleWifi();
    delay(DELAYVAL);
    pixelsUpdate(i);
    pixels.show();
    i = (i + 1) % (NUMPIXELS + MAXPIXELS);
  }
}

void MainApp::loop() {}

void handleWifi() {
  static String incoming;
  static WiFiClient c;
  static JSONBuffer b;
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
        char b = c.read();
        if (b == '\n') {
          Serial.println("Received `" + incoming +"`");
          if (incoming == String("red")) {
            onColor = colorRed;
          } else if (incoming == String("aqua")) {
            onColor = colorAqua;
          } else if (incoming == String("off")) {
            onColor = colorNone;
          }
          incoming = String();
          break;
        }
        incoming += b;
      }
    }
  }
}

void pixelsUpdate(int i) {
  int lowPixel = i - MAXPIXELS;
  
  if (i < NUMPIXELS) {
    pixels.setPixelColor(i, onColor);
  } 
  if (lowPixel >= 0) {
    pixels.setPixelColor(lowPixel, colorIndigo);
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
