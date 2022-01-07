//
// App
// Arduino Application Interface
//
// Hoani Bryson (github.com/hoani)
// Copyright (c) 2022 Hoani Bryson
// License - MIT
//

#ifndef _ESPLEDS_APP_H_ 
#define _BITTLEET_APP_H_

class App {
public:
    virtual void setup() = 0;
    virtual void loop() = 0;
};


#endif // _BITTLEET_APP_H_
