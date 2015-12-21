#include "GnusbuinoMIDI.h"
#include "AnalogMultiplexerPin.h"

#define NOISE_RATIO 10
#define DELAY_AFTER_READ 5
#define NUM_CHANNEL 4

uint8_t selected[NUM_CHANNEL] = {4,5,6,7};
//uint8_t selected[NUM_CHANNEL] = {0,1,2,3};
//uint8_t selected[NUM_CHANNEL] = {0,1,2,3,4,5,6,7};

//multiplexer setup
#define _S1 1
#define _S2 0
#define _S3 4

//analog pin connected to multiplexer
#define MULTIPLEXED_ANALOG_PIN 2  

AnalogMultiplexerPin multiplexer;

uint8_t channel;

uint8_t values[8]       = {0,0,0,0,0,0,0,0};
uint8_t values_old[8]   = {1,1,1,1,1,1,1,1};
uint8_t value_order[8]  = {3,0,1,2,5,7,6,4}; //remap multiplexer pin

void setup ( ) {
    MIDI.init();
    multiplexer.setup(_S1, _S2, _S3, MULTIPLEXED_ANALOG_PIN);
    for (channel = 0; channel < NUM_CHANNEL; channel++) {
      multiplexer.setInitialValue(value_order[channel]);
    }
}

uint8_t readChannel (unsigned char num, unsigned char order )
{
    // read value
    values[order] = multiplexer.read(value_order[num], NOISE_RATIO)>>3;  
    
    #ifdef DELAY_AFTER_READ
    MIDI.delay(DELAY_AFTER_READ);
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

  MIDI.flush();
  
}

