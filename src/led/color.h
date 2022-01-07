//
// Color
// Color definition for leds.
//
// Hoani Bryson (github.com/hoani)
// Copyright (c) 2022 Hoani Bryson
// License - MIT
//

#ifndef _ESPLEDS_LED_COLOR_H_
#define _ESPLEDS_LED_COLOR_H_

#include <stdint.h>

class Color {
public:
    Color() = default;
    Color(uint8_t r, uint8_t g, uint8_t b) 
        : r(r), g(g), b(b){};
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
};

#endif // _ESPLEDS_LED_COLOR_H_
