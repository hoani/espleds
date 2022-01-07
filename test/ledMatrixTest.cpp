//
// Hoani Bryson (github.com/hoani)
// Copyright (c) 2022 Hoani Bryson
// License - MIT
//

#include "catch.hpp"

#include <vector>

#include "Arduino.h"

#include "mock/LEDStrip.h"
#include "led/matrix.h"

#include "Helpers.h"

TEST_CASE("LEDColumn::set", "[ledMatrix]") {
    SECTION("Normal"){
        MockStrip s = MockStrip(3);

        LEDColumn column = LEDColumn(s, 3);

        column.set(0, Color(1, 0, 0));
        column.set(1, Color(0, 2, 0));
        column.set(2, Color(0, 0, 3));
        s.show();

        REQUIRE_EQUAL(Color(1, 0, 0), s.get(0));
        REQUIRE_EQUAL(Color(0, 2, 0), s.get(1));
        REQUIRE_EQUAL(Color(0, 0, 3), s.get(2));
    }

    SECTION("Reversed"){
        MockStrip s = MockStrip(3);

        LEDColumn column = LEDColumn::Reversed(s, 3);

        column.set(0, Color(1, 0, 0));
        column.set(1, Color(0, 2, 0));
        column.set(2, Color(0, 0, 3));
        s.show();

        REQUIRE_EQUAL(Color(0, 0, 3), s.get(0));
        REQUIRE_EQUAL(Color(0, 2, 0), s.get(1));
        REQUIRE_EQUAL(Color(1, 0, 0), s.get(2));
    }

    SECTION("Offset"){
        MockStrip s = MockStrip(4);

        LEDColumn column = LEDColumn(s, 3, 1);

        column.set(0, Color(1, 0, 0));
        column.set(1, Color(0, 2, 0));
        column.set(2, Color(0, 0, 3));
        s.show();

        REQUIRE_EQUAL(Color(0, 0, 0), s.get(0));
        REQUIRE_EQUAL(Color(1, 0, 0), s.get(1));
        REQUIRE_EQUAL(Color(0, 2, 0), s.get(2));
        REQUIRE_EQUAL(Color(0, 0, 3), s.get(3));
    }
}


TEST_CASE("LEDMatrix::set", "[ledMatrix]" ) 
{ 
    SECTION("1x1"){
        MockStrip s = MockStrip(1);

        LEDColumn columns[1] = {
            LEDColumn(s, 1),
        };

        LEDMatrix m = LEDMatrix(columns, 1);

        m.set(0, 0, Color(255,0,0));
        s.show();

        REQUIRE_EQUAL(Color(255,0,0), s.get(0));
    }

    SECTION("3x3"){
        MockStrip s0 = MockStrip(3);
        MockStrip s1 = MockStrip(3);
        MockStrip s2 = MockStrip(3);

        LEDColumn columns[3] = {
            LEDColumn(s0, 3),
            LEDColumn(s1, 3),
            LEDColumn(s2, 3),
        };

        LEDMatrix m = LEDMatrix(columns, 3);

        for (int i = 0; i<3; i++) {
            for (int j = 0; j<3; j++) {
                m.set(i, j, Color(255,i,j));
            }
        }
        s0.show();
        s1.show();
        s2.show();

        for (int i=0; i<3; i++) {
            REQUIRE_EQUAL(Color(255,i,0), s0.get(i));
            REQUIRE_EQUAL(Color(255,i,1), s1.get(i));
            REQUIRE_EQUAL(Color(255,i,2), s2.get(i));
        }
    }

    SECTION("3x3 Single Strip"){
        MockStrip s = MockStrip(9);

        LEDColumn columns[3] = {
            LEDColumn(s, 3),
            LEDColumn::Reversed(s, 3, 3),
            LEDColumn(s, 3, 6),
        };

        LEDMatrix m = LEDMatrix(columns, 3);

        for (int i = 0; i<3; i++) {
            for (int j = 0; j<3; j++) {
                m.set(i, j, Color(255,i,j));
            }
        }
        s.show();

        for (int i=0; i<3; i++) {
            REQUIRE_EQUAL(Color(255,i,0), s.get(i));
            REQUIRE_EQUAL(Color(255,i,1), s.get(5-i));
            REQUIRE_EQUAL(Color(255,i,2), s.get(6+i));
        }
    }
}


