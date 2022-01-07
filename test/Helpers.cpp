//
// Test Helpers
//
// Hoani Bryson (github.com/hoani)
// Copyright (c) 2022 Hoani Bryson
// License - MIT
//

#include <iostream>

#include "Helpers.h"


void NEAR(double expected, double result, double tol){
    if (fabs(expected - result) > tol) {
        std::ostringstream str;
        str << "difference between " << expected << " and "<< result <<" is greater than " << tol;
        FAIL(str.str());
    }
}
