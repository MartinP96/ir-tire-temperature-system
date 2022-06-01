#ifndef _IR_TIRE_SYSTEM_INPUTS
#define _IR_TIRE_SYSTEM_INPUTS

#include <Wire.h>
#include <Arduino.h>

#define btn_ok_pin B12
#define btn_up_pin B12
#define btn_down_pin B14
#define btn_back_pin B15

class IR_Tire_System_Inputs
{
public:
  void iniInputs(void);
  void readInputs(void);

};



#endif
