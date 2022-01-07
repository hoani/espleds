//
// LED Strip
// Interface which manipulates an LED Strip.
//
// Hoani Bryson (github.com/hoani)
// Copyright (c) 2022 Hoani Bryson
// License - MIT
//

#ifndef _ESPLEDS_MOCK_LED_STRIP_H_
#define _ESPLEDS_MOCK_LED_STRIP_H_

#include <stdint.h>
#include <stdbool.h>
#include <vector>

#include "led/strip.h"

class MockStrip : public LEDStrip {
public:
    MockStrip(int length) : _length(length), _strip(std::vector<Color>(length)), _pending(std::vector<Color>(length)){}

    void set(int index, Color color){
        if (index < _length) {
            _pending[index] = color;
        }
    }

    void show() {
        for (int i = 0; i<_length; i++) {
            _strip[i] = _pending[i];
        }
    }

    void clear() {
        for (Color& c : _strip) {
            c = Color(0, 0, 0);
        }

        for (Color& c : _pending) {
            c = Color(0, 0, 0);
        }
    }

    int length() {
        return _length;
    }

    Color get(int index) {
        if (index < _length) {
            return _strip[index];
        }
        return Color(0,0,0);
    }

private:
    int _length = 0;
    std::vector<Color> _strip;
    std::vector<Color> _pending;
};

#endif // _ESPLEDS_ADAFRUIT_LED_STRIP_H_
