#include <Stepper.h>
#include <Ps3Controller.h>

const int step_pin_x = 14; //Step Pin for X direction
const int step_pin_y = 27; //Step Pin for Y direction
const int dir_pin_x = 32; //Direction Pin for X direction
const int dir_pin_y = 33; //Direction Pin for Y direction


Stepper stepper_x(200, step_pin_x, dir_pin_x); //Create stepper_x object and with 200 steps (one revolution)
Stepper stepper_y(200, step_pin_y, dir_pin_y); //Create stepper_y object and with 200 steps (one revolution)


void test() //This function is used to test the controller inputs on the serial monitor.
{
   /*if( abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2 ) //Tests left analog stick
   {
       Serial.print("Left analog stick is moving:");
       Serial.print(" x="); Serial.print(Ps3.data.analog.stick.lx, DEC);
       Serial.print(" y="); Serial.print(Ps3.data.analog.stick.ly, DEC);
       Serial.println();
    }*/
}
void onConnect(){ //Prints "Connected if Bluetooth connection is successful
    Serial.println("Connected.");
}

void setup() {

   Serial.begin(115200);
   Ps3.attach(notify);
   Ps3.attachOnConnect(onConnect);
   Ps3.begin("00:12:34:56:78:90"); //MAC address for PS3 Controller

   Serial.println("Ready.");
}
 void loop() {
  int lx = Ps3.data.analog.stick.lx; //Setting variable for left analog stick in x direction
  int ly = Ps3.data.analog.stick.ly; //Setting variable for left analog stick in y direction
  int Map_lx_P = 1;  
  int Map_lx_N = 1;

  int Map_ly_N = 1;
  int Map_ly_P = 1;

  Map_lx_P = map(lx, 1, 127, 1, 800); //Since analog stick reads in a signed byte (-127 to 127) we make it read positive values from the x direction.
  Map_lx_N = map(lx, 1,-127, 1, 800); ////Since analog stick reads in a signed byte (-127 to 127) we make it read negative values from the x direction.

  
  Map_ly_P = map(ly, 1, 127, 1, 800); //Since analog stick reads in a signed byte (-127 to 127) we make it read positive values from the y direction.
  Map_ly_N = map(ly, 1,-127, 1, 800); //Since analog stick reads in a signed byte (-127 to 127) we make it read negative values from the y direction.
  

  if(lx > 2) //If lx > 2 make speed the Max_lx_P variable and increment it by 2 steps
  {
    stepper_x.setSpeed(Map_lx_P);
    stepper_x.step(2);

  }

  if(lx < -2) //If lx < -2 make speed the Max_lx_N variable and increment it by 2 steps
  {
    stepper_x.setSpeed(Map_lx_N);
    stepper_x.step(-2);
  }

   if(ly > 2) //If ly > 2 make speed the Max_lx_P variable and increment it by 2 steps
  {
    stepper_y.setSpeed(Map_ly_P);
    stepper_y.step(2);

  }

  if(ly < -2) //If ly < -2 make speed the Max_lx_P variable and increment it by 2 steps
  {
    stepper_y.setSpeed(Map_ly_N);
    stepper_y.step(-2);
  }
 }
  

  
