//
// Test Helpers
//
// Hoani Bryson (github.com/hoani)
// Copyright (c) 2022 Hoani Bryson
// License - MIT
//

#ifndef _ESPLEDS_TEST_HELPERS_H_
#define _BITTLEET_TEST_HELPERS_H_

#include "catch.hpp"
#include "led/matrix.h"

void NEAR(double expected, double result, double tol);
void REQUIRE_EQUAL(Color e, Color r);

# endif // _BITTLEET_TEST_HELPERS_H_