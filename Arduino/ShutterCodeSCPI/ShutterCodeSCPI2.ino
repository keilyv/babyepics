#include "Arduino.h"                                      //including the Arduino libraries
#include "Vrekrer_scpi_parser.h"                          //including the SCPI libraries
#include "Servo.h"                                        //including Servo libraries

SCPI_Parser my_instrument;                                //starts the SCPI command library
Servo myservo;                                            //creates a Servo called "myservo"
#define servoPin 3                                        //defines the Servo pin variable to pin 3
int pos = 0;                                              //places the position at start equal to 0

void setup() {
  my_instrument.RegisterCommand(F("ID?"), &Identify);     //first command "ID?"
  my_instrument.SetCommandTreeBase(F("SER:"));            //beginning to all other commands falls under the "SER"vo tree
    my_instrument.RegisterCommand(F(":?"), &ServoPos);    //gives position value of the Servo
    my_instrument.RegisterCommand(F(":UP"), &ServoUp);    //moves the Servo into the "UP" or blocking position
    my_instrument.RegisterCommand(F(":DOwn"), &ServoDown);//moves the Servo into the "DO"wn or not blocking position
  Serial.begin(9600);                                     //begins the Serial.monitor sequence
  myservo.attach(servoPin);                               //connects the name 'myservo' to the pin the Servo is attached to
}

void loop() {
  my_instrument.ProcessInput(Serial, "\n");               //starts allowing the Serial Monitor input for SCPI use

}

void Identify(SCPI_C commands, SCPI_P parameters, Stream& interface) {      //identifying what object you're using
  interface.println(F("this is the shutter, baby!"));                       //printing this line to the Serial Monitor
}

void ServoPos(SCPI_C commands, SCPI_P parameters, Stream& interface) {      //finding the position of the Servo (either 90 or 0)
  interface.println(String(pos, DEC));                                      //prints position of servo blocker
//  if(pos == 90){                                                            //if the pos value is = to 90
//    Serial.println("up");                                                       //prints up
//  }else{                                                                    //else
//    Serial.println("down");                                                     //prints down
//  }
}

void ServoUp(SCPI_C commands, SCPI_P parameters, Stream& interface){        //moves Servo UP to blocking position   
  myservo.write(90);                                                        //moves Servo to 90 degrees UP
  delay(100);                                                               //delays 100 ms
  pos = 90;                                                                 //changes the value of the position to 90
  Serial.println("now up!");                                                //prints the line 
}

void ServoDown(SCPI_C commands, SCPI_P parameters, Stream& interface){      //moves Servo down to not blocking position
  myservo.write(0);                                                         //moves Servo to 0 degrees DOwn
  delay(100);                                                               //delays 100 ms
  pos = 0;                                                                  //changes the value of the position to 0
  Serial.println("now down!");                                              //prints the line
}
