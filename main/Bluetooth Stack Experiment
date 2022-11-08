#include <stdio.h>
#include "driver/gpio.h"
#include "esp_timer.h"
#include "driver/adc.h"


//GPIO Config
#define LEDPIN 4;
//ADC Config
#define DEFAULT_VREF    1100        //Use adc2_vref_to_gpio() to obtain a better estimate
#define NO_OF_SAMPLES   64          //Multisampling

//Arduino stepper.h files (modified for ESP32)
class Stepper {
  public:
    // constructors:
    Stepper(int number_of_steps, gpio_num_t motor_pin_1, gpio_num_t motor_pin_2);
    Stepper(int number_of_steps, gpio_num_t motor_pin_1, gpio_num_t motor_pin_2,
                                 gpio_num_t motor_pin_3, gpio_num_t motor_pin_4);
    Stepper(int number_of_steps, gpio_num_t motor_pin_1, gpio_num_t motor_pin_2,
                                 gpio_num_t motor_pin_3, gpio_num_t motor_pin_4,
                                 gpio_num_t motor_pin_5);

    // speed setter method:
    void setSpeed(long whatSpeed);

    // mover method:
    void step(int number_of_steps);

    int version(void);

  private:
    void stepMotor(int this_step);

    int direction;            // Direction of rotation
    unsigned long step_delay; // delay between steps, in us, based on speed
    int number_of_steps;      // total number of steps this motor can take
    int pin_count;            // how many pins are in use.
    int step_number;          // which step the motor is on

    // motor pin numbers:
    gpio_num_t motor_pin_1;
    gpio_num_t motor_pin_2;
    gpio_num_t motor_pin_3;
    gpio_num_t motor_pin_4;
    gpio_num_t motor_pin_5;          // Only 5 phase motor

    unsigned long last_step_time; // timestamp in us of when the last step was taken
};


Stepper::Stepper(int number_of_steps, gpio_num_t motor_pin_1, gpio_num_t motor_pin_2,
                                      gpio_num_t motor_pin_3, gpio_num_t motor_pin_4)
{
  this->step_number = 0;    // which step the motor is on
  this->direction = 0;      // motor direction
  this->last_step_time = 0; // timestamp in us of the last step taken
  this->number_of_steps = number_of_steps; // total number of steps for this motor

  // Arduino pins for the motor control connection:
  this->motor_pin_1 = motor_pin_1;
  this->motor_pin_2 = motor_pin_2;
  this->motor_pin_3 = motor_pin_3;
  this->motor_pin_4 = motor_pin_4;

  // setup the pins on the microcontroller:
  gpio_set_direction(this->motor_pin_1, GPIO_MODE_OUTPUT);
  gpio_set_direction(this->motor_pin_2, GPIO_MODE_OUTPUT);
  gpio_set_direction(this->motor_pin_3, GPIO_MODE_OUTPUT);
  gpio_set_direction(this->motor_pin_4, GPIO_MODE_OUTPUT);

  // pin_count is used by the stepMotor() method:
  this->pin_count = 4;
}

void Stepper::setSpeed(long whatSpeed)
{
  this->step_delay = 60L * 1000L * 1000L / this->number_of_steps / whatSpeed;
}

/*
 * Moves the motor steps_to_move steps.  If the number is negative,
 * the motor moves in the reverse direction.
 */
void Stepper::step(int steps_to_move)
{
  int steps_left = abs(steps_to_move);  // how many steps to take

  // determine direction based on whether steps_to_mode is + or -:
  if (steps_to_move > 0) { this->direction = 1; }
  if (steps_to_move < 0) { this->direction = 0; }


  // decrement the number of steps, moving one step each time:
  while (steps_left > 0)
  {
    unsigned long now = esp_timer_get_time();
    // move only if the appropriate delay has passed:
    if (now - this->last_step_time >= this->step_delay)
    {
      // get the timeStamp of when you stepped:
      this->last_step_time = now;
      // increment or decrement the step number,
      // depending on direction:
      if (this->direction == 1)
      {
        this->step_number++;
        if (this->step_number == this->number_of_steps) {
          this->step_number = 0;
        }
      }
      else
      {
        if (this->step_number == 0) {
          this->step_number = this->number_of_steps;
        }
        this->step_number--;
      }
      // decrement the steps left:
      steps_left--;
      // step the motor to step number 0, 1, ..., {3 or 10}
      if (this->pin_count == 5)
        stepMotor(this->step_number % 10);
      else
        stepMotor(this->step_number % 4);
    }
  }
}

/*
 * Moves the motor forward or backwards.
 */
void Stepper::stepMotor(int thisStep)
{
  
  if (this->pin_count == 4) {
    switch (thisStep) {
      case 0:  // 1010
        gpio_set_level(motor_pin_1, 1);
        gpio_set_level(motor_pin_2, 0);
        gpio_set_level(motor_pin_3, 1);
        gpio_set_level(motor_pin_4, 0);
      break;
      case 1:  // 0110
        gpio_set_level(motor_pin_1, 0);
        gpio_set_level(motor_pin_2, 1);
        gpio_set_level(motor_pin_3, 1);
        gpio_set_level(motor_pin_4, 0);
      break;
      case 2:  //0101
        gpio_set_level(motor_pin_1, 0);
        gpio_set_level(motor_pin_2, 1);
        gpio_set_level(motor_pin_3, 0);
        gpio_set_level(motor_pin_4, 1);
      break;
      case 3:  //1001
        gpio_set_level(motor_pin_1, 1);
        gpio_set_level(motor_pin_2, 0);
        gpio_set_level(motor_pin_3, 0);
        gpio_set_level(motor_pin_4, 1);
      break;
    }
  }
}

void ADC_Init()
{
  //Use GPIO 26 w/ ADC2
  adc_power_on;
  adc2_config_channel_atten((adc2_channel_t)ADC_CHANNEL_9, ADC_ATTEN_DB_0);             //GPIO 26, 0Db Attenuation (ensure voltage on pin <2.5v)
  adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t *adc_chars));
  esp_adc_cal_value_t val_type = esp_adc_cal_characterize(ADC_UNIT2, ADC_ATTEN_DB_0, ADC_WIDTH_BIT_12, DEFAULT_VREF, adc_chars);
  print_char_val_type(val_type);


}


void app_main(void)
{
    
  Stepper myStepper(2048,GPIO_NUM_27, GPIO_NUM_15, GPIO_NUM_33, GPIO_NUM_32);             //Hardcoded for Faisals circuit
  myStepper.setSpeed(11)                                                                  //Speed set by that weird formula

  
}

