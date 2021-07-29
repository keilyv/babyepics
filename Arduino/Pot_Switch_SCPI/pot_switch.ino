#include "Arduino.h" 
#include "Vrekrer_scpi_parser.h" 

SCPI_Parser my_instrument;
const int potPin = A0;    // select the input pin for the potentiometer
const int rockerPin = 7;   // select the pin for the rocker
int val = 0;       // variable to store the value coming from the potentiometer
int state = 0;    // variable to store state of rocker

void setup() {
  my_instrument.RegisterCommand(F("ID?"), &Identify); 
  my_instrument.RegisterCommand(F("POT?"), &Potentiometer); 
  my_instrument.RegisterCommand(F("ROC?"), &RocPos);  
  Serial.begin(9600);
  pinMode(rockerPin, INPUT);
  pinMode(potPin, INPUT);
}

void loop() {
  my_instrument.ProcessInput(Serial, "\n");
}

void Identify(SCPI_C commands, SCPI_P parameters, Stream& interface) { 
  interface.println(F("Rocker/Potentiometer System")); 
}

void Potentiometer(SCPI_C commands, SCPI_P parameters, Stream& interface) { 
  val = analogRead(A0);
  interface.println(String(val, DEC)); 
}

void RocPos(SCPI_C commands, SCPI_P parameters, Stream& interface) { 
  state = digitalRead(rockerPin);
  switch(state){
    case 0:
    interface.println(F("OFF")); //prints state of switch
    break;
    case 1:
    interface.println(F("ON")); //prints state of switch
    break;
    default:
    interface.println(F("Broken")); //prints state of switch
  }
  //interface.println(String(state,DEC)); //prints state of switch
}
