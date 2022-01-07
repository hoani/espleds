//
// Main sketch for ESP LEDs
//
// Hoani Bryson (github.com/hoani)
// Copyright (c) 2021 Hoani Bryson
// License - MIT
//

#include "src/app/MainApp.h"
App* app = new MainApp();

void setup() {
  app->setup();
}

void loop() {
  app->loop();
}
