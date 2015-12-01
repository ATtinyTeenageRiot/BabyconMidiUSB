//modified version of AnalogPin library by Rob Tillaart
// * added support for multiplexer (Budi Prakosa)

#ifndef AnalogMultiplexerPin_h
#define AnalogMultiplexerPin_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define AnalogMultiplexerPin_LIB_VERSION "0.1"

class AnalogMultiplexerPin
{
private:
    uint8_t _pin;
    int _prevValue[8];
    uint8_t s1;
	uint8_t s2;
	uint8_t s3;
	uint8_t z;

public:

    void setup(const uint8_t _s1, const uint8_t _s2, const uint8_t _s3, const uint8_t _z);

    void setInitialValue(uint8_t _pin_index);

    int readChannel (const uint8_t _pin_index);

    // noise 0..255; in practice 0..4
    int read(const uint8_t _pin_index, const uint8_t noise = 0);

    // alpha 0..31;
    // int readSmoothed(const uint8_t _pin_index, uint8_t alpha = 0);

    // int readPrevious(const uint8_t _pin_index);



};

#endif
// -- END OF FILE --
