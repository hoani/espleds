//
// LED Matrix
// Interface which manipulates LED strips as a matrix
//
// Hoani Bryson (github.com/hoani)
// Copyright (c) 2022 Hoani Bryson
// License - MIT
//

#ifndef _ESPLEDS_LED_MATRIX_H_
#define _ESPLEDS_LED_MATRIX_H_

#include "color.h"
#include "strip.h"

class LEDColumn{
public:
    LEDColumn(LEDStrip& strip, int len, int offset = 0, bool reverse = false) : _strip(strip), _len(len), _offset(offset), _reverse(reverse){}

    void set(int index, Color color) {
        if (index < 0) {
            return;
        }

        if (index < _len) {
            if (_reverse) {
                _strip.set(_offset + _len - (index + 1), color);
            } else {
                _strip.set(_offset + index, color);
            }
        }
    }

    static LEDColumn Reversed(LEDStrip& strip, int len, int offset = 0) {
        return LEDColumn(strip, len, offset, true);
    }

private:
    LEDStrip& _strip;
    int _len = 0;
    int _offset = 0;
    bool _reverse = false;
};

class LEDMatrix {
public:
    LEDMatrix(LEDColumn* columns, int numColumns) : _columns(columns), _m(numColumns){}

    void set(int i, int j, Color color) {
        if (j < _m) {
            _columns[j].set(i, color);
        }
    }

private:
    LEDColumn* _columns;
    int _m = 1;
};

#endif // _ESPLEDS_LED_MATRIX_H_
