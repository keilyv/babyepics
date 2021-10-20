/*
Generates 3.3 V TTL signals at a fixed repetition rate

Outputs across four channels, each with its own delay time

Following timer instructions at: https://github.com/contrem/arduino-timer

*/

#include "Arduino.h"
#include <math.h>
#include <arduino-timer.h>

Timer<10, micros, int> timer1; // TTL pulse timer with 10 task slots, microsecond resolution, and handler argument type int
Timer<1, millis> timer2; // rep-rate timer with 1 task slot, millisecond resolution, and void-type handler

#define TRIGOUT 3 // Outputs at start of trigger event
#define NCHAN 8 // Total number independently delayed output signals
#define CH0 4
#define CH1 5
#define CH2 6
#define CH3 7
#define CH4 8
#define CH5 9
#define CH6 10
#define CH7 11

int chanPins[NCHAN]; // Pins for each channel
int delays[NCHAN]; // Millisecond delay times for each channel

int pulseTime = 3000; // TTL pulse duration in microseconds
unsigned long t0;

bool TTLStop(int chanPin) {
    // Bring this pulse output back to LOW
    digitalWrite(chanPin, LOW);
    return false; // to repeat the action - false to stop
}

bool TTLStart(int chanPin) {
    // Bring this channel output to HIGH
    digitalWrite(chanPin, HIGH);
    timer1.in(pulseTime, TTLStop, chanPin); // Start a timer to bring this signal back to LOW
    return false; // to repeat the action - false to stop
}

bool trigStart(void *argument){
    if (timer1.size() < 1) { // Only start a new set of triggers if the old set is completed
      t0 = micros() + 1000; // Set "time zero" two thousand microseconds into the future to get everything set up first

      // Schedule the "TRIGOUT" / t0 pulse
      timer1.at(t0, TTLStart, TRIGOUT);
      
      // Schedule the channel pulses
      for(int i = 0; i < NCHAN; ++i)
      {
          timer1.at(t0 + delays[i], TTLStart, chanPins[i]); // Start a timer for this channel
      }
    }
    return true; // repeat at the next interval of the timer
}

void updateRepRate(double repRate){
  // Sets the repetition-rate, with value in Hz
  timer2.cancel();
  int repTime = round(1000 / repRate);
  timer2.every(repTime, trigStart); // Start a timer for this channel
  Serial.print("Hello!");
  Serial.print(repTime);
}

void setup() {
  Serial.begin(9600);
  
  pinMode(TRIGOUT, OUTPUT); // Declare the TRIGOUT pin as a digital output
  pinMode(CH0, OUTPUT);
  pinMode(CH1, OUTPUT);
  pinMode(CH2, OUTPUT);
  pinMode(CH3, OUTPUT);  
  pinMode(CH4, OUTPUT);
  pinMode(CH5, OUTPUT);
  pinMode(CH6, OUTPUT);
  pinMode(CH7, OUTPUT);

  // Save pin numbers into the chanPins array
  chanPins[0] = CH0;
  chanPins[1] = CH1;
  chanPins[2] = CH2;
  chanPins[3] = CH3;
  chanPins[4] = CH4;
  chanPins[5] = CH5;
  chanPins[6] = CH6;
  chanPins[7] = CH7;
    
  // Save initial delay times (in milliseconds) into the delays array
  delays[0] = 1900;
  delays[1] = 2000;
  delays[2] = 2100;
  delays[3] = 2000;
  delays[4] = 2000;
  delays[5] = 2000;
  delays[6] = 2000;
  delays[7] = 2000;

  // Initialize the repetition rate at 10 Hz
  double repRate = 10;
  updateRepRate(repRate); // Sets the repetition-rate, with value in Hz
}

void loop() {
  timer1.tick();
  timer2.tick();
}
