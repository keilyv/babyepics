#include "Arduino.h"
#include "Vrekrer_scpi_parser.h"

SCPI_Parser my_instrument;
#define photoPin A0
int inten = 0;

void setup() {
  // put your setup code here, to run once:
  my_instrument.RegisterCommand(F("ID?"), &Identify);
  my_instrument.SetCommandTreeBase(F("PHO:"));
    my_instrument.RegisterCommand(F(":?"), &ServoPos);
  Serial.begin(9600);
  //Serial.println("hello");
}

void loop() {
  my_instrument.ProcessInput(Serial, "\n");

}

void Identify(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  interface.println(F("this is the photodiode, baby!"));
  interface.println(F("low number means bright, high number means dark"));
}

void ServoPos(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  inten = analogRead(photoPin);
  interface.println(String(inten, DEC)); //prints intensity of the photodiode
}
