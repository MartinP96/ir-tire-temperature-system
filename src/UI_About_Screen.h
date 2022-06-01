#ifndef _UI_ABOUT_SCREEN_H_
#define _UI_ABOUT_SCREEN_H_

#include <Arduino.h>
#include "IR_Tire_System.h"
#include "Float_To_String.h"
#include <MCUFRIEND_kbv.h>
#include "UI_Colors.h"


class AboutScreen
{
public:

  AboutScreen():lcd{NULL},screen_displayed{false}, display_time{0}{
  }

  void iniScreen(MCUFRIEND_kbv *ptr);
  void displayScreen(IR_Tire_System &sys, unsigned long sys_time);
  void resetState(void);

private:

  MCUFRIEND_kbv *lcd;

  void displayScreenCore(void);
  void moveSelector(int pos);
  void displayParamVal(void);

  bool screen_displayed;
  unsigned long display_time;
};

#endif
