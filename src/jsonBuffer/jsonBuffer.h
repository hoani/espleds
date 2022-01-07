//
// JSON Buffer
// Takes bytes off a stream and feeds them into a buffer.
//
// Hoani Bryson (github.com/hoani)
// Copyright (c) 2022 Hoani Bryson
// License - MIT
//

#ifndef _JSON_BUFFER_H_
#define _JSON_BUFFER_H_

#include <stdint.h>
#include <stdbool.h>


template <size_t N = 256>
class JSONBuffer {
  public:
    JSONBuffer() = default;

    void update(Stream& stream){
        if (_done || _index >= N) {
            return;
        }

        while (stream.available() > 0) {
            byte b = stream.read();
            _buffer[_index++] = b;
            if (b == '{') {
                _depth += 1;
            } else if (b == '}'){
                if (_depth > 0) {
                    _depth--;
                    if (_depth == 0) {
                        _done = true;
                        return;
                    }
                }
            }
        }
    }

    bool done() { return _done; }



  protected:
    char _buffer[N];
    size_t _index = 0;
    bool _done = false;
    int _depth = 0;
    
};


#endif // _JSON_BUFFER_H_