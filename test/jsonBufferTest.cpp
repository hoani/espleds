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
        JSONBuffer<128> b{};
        Serial.buffer = "{\"msg\":\"Hello\"}";
        b.update(Serial);

        REQUIRE(Serial.buffer.empty());
    }

    SECTION("Does not read additional bytes"){
        JSONBuffer<128> b{};
        Serial.buffer = "{\"msg\":\"Hello\"}{\"msg2\":";
        b.update(Serial);

        REQUIRE(String(Serial.buffer.data()) == String("{\"msg2\":"));
    }
}

TEST_CASE("getString", "[JSONBuffer]" ) 
{
    SECTION("empty when not done"){
        JSONBuffer<128> b{};
        Serial.buffer = "{\"msg\":\"Hello\"";
        b.update(Serial);

        REQUIRE(b.getString() == String(""));
    }

    SECTION("correct contents when done"){
        JSONBuffer<128> b{};
        Serial.buffer = "{\"msg\":\"Hello\"}";
        b.update(Serial);

        REQUIRE(b.getString() == String("{\"msg\":\"Hello\"}"));
    }

    SECTION("reject garbage bytes"){
        JSONBuffer<128> b{};
        Serial.buffer = "\"Garbage\":12345}{\"msg\":\"Hello\"}";
        b.update(Serial);

        REQUIRE(b.getString() == String("{\"msg\":\"Hello\"}"));
    }

    SECTION("multibuffering"){
        Serial.buffer = "{\"msg\":\"Hello\"}{\"name\":\"Tony\",\"age\":37}{\"cmds\":[{\"left\": 5},{\"stop\":0}]}";
        std::vector<String> expectedBuffers = {
            "{\"msg\":\"Hello\"}",
            "{\"name\":\"Tony\",\"age\":37}",
            "{\"cmds\":[{\"left\": 5},{\"stop\":0}]}",
        };
        for (const String& expected : expectedBuffers) {
            JSONBuffer<128> b{};
            b.update(Serial);

            REQUIRE(b.done());
            REQUIRE(b.getString() == expected);
        }

        JSONBuffer<128> b{};
        b.update(Serial);

        REQUIRE(b.done() == false);
    }

    SECTION("reject buffers which are too large"){
        JSONBuffer<16> b{};
        Serial.buffer = "{\"Too large\":true,\"Garbage\":12345}{\"msg\":\"Hello\"}";
        b.update(Serial);

        REQUIRE(b.getString() == String("{\"msg\":\"Hello\"}"));
    }

    SECTION("multiple update"){
        JSONBuffer<128> b{};
        Serial.buffer = "{\"msg\":";
        b.update(Serial);
        REQUIRE(b.done() == false);

        Serial.buffer = "\"Hello\"}";
        b.update(Serial);
        REQUIRE(b.done());

        REQUIRE(b.getString() == String("{\"msg\":\"Hello\"}"));
    }
}

