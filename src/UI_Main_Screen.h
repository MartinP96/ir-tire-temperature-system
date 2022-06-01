#ifndef _UI_MAIN_SCREEN_H_
#define _UI_MAIN_SCREEN_H_

#include <Arduino.h>
#include "IR_Tire_System.h"
#include "Float_To_String.h"
#include <MCUFRIEND_kbv.h>
#include "UI_Colors.h"


class MainScreen
{

public:

  MainScreen() : lcd{nullptr}, screen_displayed {false}, display_time{0}, display_front{false},
  display_rear{false}, front_comm_warrning{false}, rear_comm_warrning{false},
  alert_displayed{false}{
  }

  void iniScreen(MCUFRIEND_kbv *ptr);
  void displayScreen(IR_Tire_System &sys, unsigned long sys_time);
  void resetState(void);

private:

  MCUFRIEND_kbv *lcd;

  void displayScreenCore(void);
  void displayTemperatureFront(float temp);
  void displayTemperatureRear(float temp);
  void displayTemperature(IR_Tire_System &sys);
  void checkSystemStatus(IR_Tire_System &sys);
  void displayAlert(void);
  // UI States
  bool screen_displayed;
  unsigned long display_time;

  //UI statuses
  bool display_front;
  bool display_rear;

  //UI warnings
  bool front_comm_warrning;
  bool rear_comm_warrning;
  bool alert_displayed;
  bool data_logging_warrning;

};

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////



#endif
