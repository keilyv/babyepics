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
int value = 0;


void setup() { 
  my_instrument.RegisterCommand(F("ID?"), &Identify);  
  my_instrument.RegisterCommand(F("SET"), &SetBrightness); 
  Serial.begin(9600); 
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  pinMode(led4Pin, OUTPUT);
  pinMode(led5Pin, OUTPUT);
  pinMode(led6Pin, OUTPUT);
  analogWrite(led1Pin, brightness);
  analogWrite(led2Pin, brightness);
  analogWrite(led3Pin, brightness);
  analogWrite(led4Pin, brightness);
  analogWrite(led5Pin, brightness);
  analogWrite(led6Pin, brightness); 
}

void loop() { 
  my_instrument.ProcessInput(Serial, "\r\n"); 
} 

void Identify(SCPI_C commands, SCPI_P parameters, Stream& interface) { 
  interface.println(F("LEDs Unite!"));
}

void SetBrightness(SCPI_C commands, SCPI_P parameters, Stream& interface) { 
  if(parameters.Size() > 0) {
    value = String(parameters[0]).toInt();
    brightness = constrain(value, 0, 255);
    analogWrite(led1Pin, brightness);
    analogWrite(led2Pin, brightness);
    analogWrite(led3Pin, brightness);
    analogWrite(led4Pin, brightness);
    analogWrite(led5Pin, brightness);
    analogWrite(led6Pin, brightness);
    interface.println(String(brightness, DEC));
  }
}  
