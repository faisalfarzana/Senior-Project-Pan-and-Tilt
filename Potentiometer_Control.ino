#include <Stepper.h>
#define STEPS 2048 //2048 steps

int ADC_pin = 26; //GPIO 26 for 
int val = 0;
int prev = 0;
int motor_speed = 0;
Stepper myStepper(STEPS, 27, 15, 33, 32); //Used order 1,3,2,4

void setup() {
  // set the speed at 11 rpm:
  myStepper.setSpeed(11);
  // initialize the serial port:
  Serial.begin(9600);
}
void loop() {
  val = analogRead(ADC_pin);
  motor_speed = map(val, 0, 4096, -100, 100); //mapping 4096 steps for a full rotation to -100 for cc, and 100 for c
  myStepper.step(motor_speed);
  Serial.println(motor_speed);
  prev = val;
}

