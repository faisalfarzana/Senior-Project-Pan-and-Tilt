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
#define STEPS 2048 //2048 steps

int ledPin = 4; //GPIO 4
//int POT = 15; //GPIO 15 For PWM
int ADC_pin = 26; //GPIO 26 for 
//int prevVal = 0;
int val = 0;

Stepper myStepper(STEPS, 27, 15, 33, 32);
//IN order: 1,3,2,4

void setup() {
  // set the speed at 11 rpm:
  myStepper.setSpeed(11);
  // initialize the serial port:
  Serial.begin(9600);

  //set LED as output
  pinMode(ledPin, OUTPUT);
  
}
void loop() {
  val = analogRead(ADC_pin);

  //move a number if steps equal to the change in the sensor reading
  myStepper.step(val);

  //prevVal = val; // Remember previous value
  Serial.println(val);
  
}
