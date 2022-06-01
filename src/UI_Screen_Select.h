#ifndef _UI_SCREEN_SELECT_H_
#define _UI_SCREEN_SELECT_H_

#include <Arduino.h>
#include "IR_Tire_System.h"
#include "Float_To_String.h"
#include <MCUFRIEND_kbv.h>
#include "UI_Colors.h"

class ScreenSelect
{
public:

  ScreenSelect() : lcd{nullptr}, screen_displayed {false}, display_time{0},
  menu_selector_pos{70,110,150,190}, selected_menu{66},previouse_selected_menu{0}{
  }

  void iniScreen(MCUFRIEND_kbv *ptr);
  void displayScreen(IR_Tire_System &sys, unsigned long sys_time, int menu_num);
  void resetState(void);

private:

  MCUFRIEND_kbv *lcd;

  void displayScreenCore(void);
  void moveSelector(int pos);

  bool screen_displayed;
  unsigned long display_time;

  int menu_selector_pos[4];
  int selected_menu;
  int previouse_selected_menu;
};

#endif
