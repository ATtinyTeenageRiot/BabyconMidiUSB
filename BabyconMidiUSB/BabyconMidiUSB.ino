#include "GnusbuinoMIDI.h"


unsigned char s1 = 1;
unsigned char s2 = 0;
unsigned char s3 = 4;
unsigned char z = 2;

int channel;
unsigned char values[8]       = {0,0,0,0,0,0,0,0};
unsigned char values_old[8]   = {1,1,1,1,1,1,1,1};
unsigned char value_order[8]  = {3,0,1,2,5,7,6,4};

unsigned char selected[4] = {2,3,4,7};

void setup ( ) {
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  
  pinMode(z, INPUT);
}


void readChannel (unsigned char num, unsigned char order )
{
      // set switch to output (not sure why, but must be set everytime..)
    pinMode(s1, OUTPUT);
    pinMode(s2, OUTPUT);
    pinMode(s3, OUTPUT);
    
    // select channel
    digitalWrite(s1, (value_order[num] & 0x01));
    digitalWrite(s2, ((value_order[num]>>1) & 0x01));
    digitalWrite(s3, ((value_order[num]>>2) & 0x01));
      
    // read value
    values[order] = analogRead(z)>>3;
  
}

void loop () {
  
  for (channel = 0; channel < 4; channel++) {
    
    readChannel(selected[channel], channel);
      
    if (values[channel] != values_old[channel]) {
        MIDI.write(MIDI_CONTROLCHANGE, channel+1, values[channel]);
        values_old[channel] = values[channel];
    }
  }
  
}

