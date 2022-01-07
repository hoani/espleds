//
// LED Strip
// Interface which manipulates an LED Strip.
//
// Hoani Bryson (github.com/hoani)
// Copyright (c) 2022 Hoani Bryson
// License - MIT
//

#ifndef _ESPLEDS_LED_STRIP_H_
#define _ESPLEDS_LED_STRIP_H_

#include <stdint.h>
#include <stdbool.h>

class Color {
public:
    Color(uint8_t r, uint8_t g, uint8_t b) 
        : r(r), g(g), b(b){};
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

class LEDStrip {
public:
    virtual void set(int index, Color color) = 0;
    virtual void show() = 0;
    virtual void clear() = 0;
};

#endif // _ESPLEDS_LED_STRIP_H_
