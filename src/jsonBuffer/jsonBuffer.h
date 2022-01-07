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
        if (_done) {
            return;
        }

        while (stream.available() > 0) {
            byte b = stream.read();
            if (_depth > 0) {
                _buffer[_index++] = b;
            }
            if (b == '{') {
                if (_depth == 0) {
                    _buffer[_index++] = b;
                }
                _depth += 1;
            } else if (b == '}'){
                if (_depth > 0) {
                    _depth--;
                    if (_depth == 0) {
                        _buffer[_index++] = '\0';
                        _done = true;
                        return;
                    }
                }
            }

            // Reset if we are running out of buffer.
            if ((_index + 1) == N) {
                _index = 0;
                _depth = 0;
            }
        }
    }

    bool done() { return _done; }

    String getString() {
        if (_done) {
            return String(_buffer);
        }
        return String("");
    }



  protected:
    char _buffer[N];
    size_t _index = 0;
    bool _done = false;
    int _depth = 0;
    
};


#endif // _JSON_BUFFER_H_