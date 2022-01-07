//
// Test Helpers
//
// Hoani Bryson (github.com/hoani)
// Copyright (c) 2022 Hoani Bryson
// License - MIT
//

#include <iostream>

#include "Helpers.h"
#include "led/color.h"


void NEAR(double expected, double result, double tol){
    if (fabs(expected - result) > tol) {
        std::ostringstream str;
        str << "difference between " << expected << " and "<< result <<" is greater than " << tol;
        FAIL(str.str());
    }
}

void REQUIRE_EQUAL(Color e, Color r){
    if ((e.r != r.r) || (e.g != r.g) || (e.b != r.b)) {
        std::ostringstream str;
        str << "expected " << (int)e.r << ", " << (int)e.g << ", " << (int)e.b << " got " << (int)r.r << ", " << (int)r.g << ", " << (int)r.b;
        FAIL(str.str());
    }
}
