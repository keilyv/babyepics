#include "Arduino.h" 
#include "Vrekrer_scpi_parser.h"

SCPI_Parser my_instrument;
int brightness = 0; 
const int led1Pin = 3; 
const int led2Pin = 5;
const int led3Pin = 6;
const int led4Pin = 9;
const int led5Pin = 10;
const int led6Pin = 11; 
int value = 0; // temp variable

// TODO: Attach an interrupt to this function
void pulseLEDs() {
    analogWrite(led1Pin, brightness);
    analogWrite(led2Pin, brightness);
    analogWrite(led3Pin, brightness);
    analogWrite(led4Pin, brightness);
    analogWrite(led5Pin, brightness);
    analogWrite(led6Pin, brightness);
    delayMicroseconds(10000)
    analogWrite(led1Pin, LOW);
    analogWrite(led2Pin, LOW);
    analogWrite(led3Pin, LOW);
    analogWrite(led4Pin, LOW);
    analogWrite(led5Pin, LOW);
    analogWrite(led6Pin, LOW);
}

    
void setup() { 
  my_instrument.RegisterCommand(F("*IDN?"), &identify);  
  my_instrument.RegisterCommand(F("BRIGhtness?"), &getBrightness); 
  my_instrument.RegisterCommand(F("BRIGhtness"), &setBrightness); 
  Serial.begin(9600); 
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  pinMode(led4Pin, OUTPUT);
  pinMode(led5Pin, OUTPUT);
  pinMode(led6Pin, OUTPUT);
  analogWrite(led1Pin, LOW);
  analogWrite(led2Pin, LOW);
  analogWrite(led3Pin, LOW);
  analogWrite(led4Pin, LOW);
  analogWrite(led5Pin, LOW);
  analogWrite(led6Pin, LOW); 
}

void loop() { 
  my_instrument.ProcessInput(Serial, "\r\n"); 
} 

/* Serial communication functions */
void identify(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  interface.println(F("DolphinDAQ,Arduino Triggered LEDs,#00,v0.1"));
}

void getBrightness(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  interface.println(String(brightness, DEC));
}

void setBrightness(SCPI_C commands, SCPI_P parameters, Stream& interface) { 
  if(parameters.Size() > 0) {
    value = String(parameters[0]).toInt();
    brightness = constrain(value, 0, 255);
  }
}  
