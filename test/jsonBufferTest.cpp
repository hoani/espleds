//
// Scheduler Tests
//
// Hoani Bryson (github.com/hoani)
// Copyright (c) 2022 Hoani Bryson
// License - MIT
//

#include "catch.hpp"

#include <vector>

#include "Arduino.h"

#include "jsonBuffer/jsonBuffer.h"

TEST_CASE("Done", "[JSONBuffer]" ) 
{ 
    SECTION("Is Done"){

        SECTION("Empty Object"){
            JSONBuffer<128> b{};
            Serial.buffer = "{}";
            b.update(Serial);
            
            REQUIRE(b.done() == true);
        }

        SECTION("Object"){
            JSONBuffer<128> b{};
            Serial.buffer = "{\"msg\":\"Hello\"}";
            b.update(Serial);
            
            REQUIRE(b.done() == true);
        }

        SECTION("Nesting"){
            JSONBuffer<128> b{};
            Serial.buffer = "{\"a\":1,\"b\":{\"c\":2,\"d\":3},\"e\":{}}";
            b.update(Serial);
            
            REQUIRE(b.done() == true);
        }
    }

    SECTION("Not done"){
        SECTION("Empty Buffer"){
            JSONBuffer<128> b{};
            Serial.buffer = "";
            b.update(Serial);
            
            REQUIRE(b.done() == false);
        }

        SECTION("Incomplete Object"){
            JSONBuffer<128> b{};
            Serial.buffer = "{\"msg\":\"Hello\"";
            b.update(Serial);
            
            REQUIRE(b.done() == false);
        }

        SECTION("Incomplete Nesting"){
            JSONBuffer<128> b{};
            Serial.buffer = "{\"a\":1,\"b\":{\"c\":2,\"d\":3,\"e\":{}}";
            b.update(Serial);
            
            REQUIRE(b.done() == false);
        }
    }
}

TEST_CASE("update", "[JSONBuffer]" ) 
{
    SECTION("Reads Serial"){
    }

    SECTION("Does not read additional bytes"){
    }
}

TEST_CASE("getString", "[JSONBuffer]" ) 
{
    SECTION("empty when not done"){
    }

    SECTION("correct contents when done"){

    }

    SECTION("reject garbage bytes"){

    }

    SECTION("multibuffering"){

    }
}

