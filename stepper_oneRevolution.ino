
/*
 Stepper Motor Control - one revolution

 This program drives a unipolar or bipolar stepper motor.
 The motor is attached to digital pins 8 - 11 of the Arduino.

 The motor should revolve one revolution in one direction, then
 one revolution in the other direction.


 Created 11 Mar. 2007
 Modified 30 Nov. 2009
 by Tom Igoe

 */

#include <Stepper.h>
int ledPin = 4; //GPIO 4
const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 27, 15, 33, 32);
//IN order: 1,3,2,4

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(11);
  // initialize the serial port:
  Serial.begin(9600);

  //set LED as output
  pinMode(ledPin, OUTPUT);
  
}

void loop() {
  // step one revolution  in one direction:
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  digitalWrite(ledPin,LOW);
  delay(500);
  

  // step one revolution in the other direction:
  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);
   digitalWrite(ledPin,HIGH);
  delay(500);
}
