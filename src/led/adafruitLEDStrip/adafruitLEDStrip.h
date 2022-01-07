//
// LED Strip
// Interface which manipulates an LED Strip.
//
// Hoani Bryson (github.com/hoani)
// Copyright (c) 2022 Hoani Bryson
// License - MIT
//

#ifndef _ESPLEDS_ADAFRUIT_LED_STRIP_H_
#define _ESPLEDS_ADAFRUIT_LED_STRIP_H_

#include <stdint.h>
#include <stdbool.h>

#include "../strip.h"
#include "../../3rdParty/Adafruit_NeoPixel/Adafruit_NeoPixel.h"




class AdafruitLEDStrip : public LEDStrip {
public:
    AdafruitLEDStrip(Adafruit_NeoPixel &strip) : _strip(strip){}

    void set(int index, Color color){
        _strip.setPixelColor(static_cast<uint16_t>(index), color.r, color.g, color.b);
    }

    void show() {
        _strip.show();
    }
    void clear() {
        _strip.clear();
    }

    int length() {
        static_cast<uint16_t>(_strip.numPixels());
    }

private:
    Adafruit_NeoPixel & _strip;
};

#endif // _ESPLEDS_ADAFRUIT_LED_STRIP_H_
