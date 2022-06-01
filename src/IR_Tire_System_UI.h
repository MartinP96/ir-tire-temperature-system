#ifndef _IR_TIRE_SYSTEM_UI
#define _IR_TIRE_SYSTEM_UI

#include <LiquidCrystal.h>
#include "IR_Tire_System.h"
#include "Input_buttons.h"

// Screen headers

#include "UI_Main_Screen.h"
#include "UI_Screen_Select.h"
#include "UI_Configuration_Screen.h"
#include "UI_About_Screen.h"
#include "UI_Graph_Screen.h"

#include <MCUFRIEND_kbv.h>


//////////////////////////////////////////
//          MAIN UI CLASS               //
//////////////////////////////////////////
class IR_Tire_System_UI
{
public:
  // Konstruktor
  IR_Tire_System_UI():tft_ptr{nullptr},ui_main_menu_state{0},
   display_time{0},ui_setting_menu_state{0},ui_screen_select_index{0},
   ui_screen_select_state{0},ui_configuration_screen_state{0},increment_flag{false},
   decrement_flag{false},text_displayed{false},param_saved_tmp{false}{
  }

  void lcdIni(MCUFRIEND_kbv *tft_addr);
  void displayCommStatus(bool front_status, bool rear_status);
  void menuControl(IR_Tire_System &sys, Input_buttons &input, unsigned long sys_time);

private:
  //Screens
  MainScreen main_screen;
  ScreenSelect screen_select;
  ConfigurationScreen configuration_screen;
  AboutScreen about_screen;
  GraphScreen graph_screen;

  MCUFRIEND_kbv *tft_ptr;

  // Variables
  int ui_main_menu_state;
  unsigned long display_time;
  int ui_setting_menu_state;
  int ui_screen_select_index;
  int ui_screen_select_state;
  int ui_configuration_screen_state;
  bool increment_flag;
  bool decrement_flag;
  bool text_displayed;
  bool param_saved_tmp;

};


#endif
