//modified version of AnalogPin library by Rob Tillaart
// * added support for multiplexer (Budi Prakosa)

#include "AnalogMultiplexerPin.h"


void AnalogMultiplexerPin::setup(const uint8_t _s1, const uint8_t _s2, const uint8_t _s3, const uint8_t _z)
{
    s1 = _s1;
    s2 = _s2;
    s3 = _s3;
    z =  _z; //analog pin connected to multiplexer

    pinMode(s1, OUTPUT);
    pinMode(s2, OUTPUT);
    pinMode(s3, OUTPUT);
    pinMode(z, INPUT);

    //set initial value
    _prevValue[0] = 0;
    _prevValue[1] = 0;
    _prevValue[2] = 0;
    _prevValue[3] = 0;
    _prevValue[4] = 0;
    _prevValue[5] = 0;
    _prevValue[6] = 0;
    _prevValue[7] = 0;
    
}


int AnalogMultiplexerPin::readChannel (const uint8_t _pin_index)
{
    // set switch to output (not sure why, but must be set everytime..)
    pinMode(s1, OUTPUT);
    pinMode(s2, OUTPUT);
    pinMode(s3, OUTPUT);
    
    // set multiplexer, select channel
    digitalWrite(s1, (_pin_index & 0x01));
    digitalWrite(s2, ((_pin_index>>1) & 0x01));
    digitalWrite(s3, ((_pin_index>>2) & 0x01));
      
    // read value
    return analogRead(z);
}


void AnalogMultiplexerPin::setInitialValue(uint8_t _pin_index)
{
    _prevValue[_pin_index] = readChannel(_pin_index);
}


int AnalogMultiplexerPin::read(const uint8_t _pin_index, const uint8_t noise)
{
    int value = readChannel(_pin_index);
    if (noise == 0 || ((value - _prevValue[_pin_index]) & 0x7FFF) > noise)
    {
        _prevValue[_pin_index] = value;
    }
    return _prevValue[_pin_index];
}


// int AnalogMultiplexerPin::readSmoothed(const uint8_t _pin_index, uint8_t alpha)
// {
//     if (alpha > 31) alpha = 31;
//     int value = readChannel(_pin_index);
//     if (alpha > 0)
//     {
//         value = value + (alpha * (_prevValue[_pin_index] - value)) / 32;
//     }
//     _prevValue[_pin_index] = value;
//     return value;
// }


// int AnalogMultiplexerPin::readPrevious(const uint8_t _pin_index)
// {
//     return _prevValue[_pin_index];
// }
// -- END OF FILE --
