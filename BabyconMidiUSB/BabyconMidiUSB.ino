#include "GnusbuinoMIDI.h"
#include "AnalogMultiplexerPin.h"

#define NOISE_RATIO 10
//#define DELAY_AFTER_READ 5
#define NUM_CHANNEL 4

unsigned char selected[NUM_CHANNEL] = {4,5,6,7};
//unsigned char selected[NUM_CHANNEL] = {0,1,2,3};

#define _S1 1
#define _S2 0
#define _S3 4
#define MULTIPLEXED_ANALOG_PIN 2  //analog pin connected to multiplexer

AnalogMultiplexerPin multiplexer;

int channel;

unsigned char values[8]       = {0,0,0,0,0,0,0,0};
unsigned char values_old[8]   = {1,1,1,1,1,1,1,1};
unsigned char value_order[8]  = {3,0,1,2,5,7,6,4};

void setup ( ) {
    multiplexer.setup(_S1, _S2, _S3, MULTIPLEXED_ANALOG_PIN);
    delay(100);
    for (channel = 0; channel < NUM_CHANNEL; channel++) {
      multiplexer.setInitialValue(value_order[channel]);
    }
}

void readChannel (unsigned char num, unsigned char order )
{
    // read value
    values[order] = multiplexer.read(value_order[num], NOISE_RATIO)>>3;  
    
    #ifdef DELAY_AFTER_READ
    delay(DELAY_AFTER_READ);
    #endif
}

void loop () {
  
  for (channel = 0; channel < NUM_CHANNEL; channel++) {    
    readChannel(selected[channel], channel);      
    if (values[channel] != values_old[channel]) {
        MIDI.write(MIDI_CONTROLCHANGE, channel+1, values[channel]);
        values_old[channel] = values[channel];
    }
  }
  
}

