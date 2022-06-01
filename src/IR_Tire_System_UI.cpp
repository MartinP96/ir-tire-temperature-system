#include "IR_Tire_System_UI.h"
#include <Arduino.h>
#include <String.h>

/****************************************
            Class Constructor
*****************************************/


/****************************************
          Basic getter and setters
*****************************************/


/****************************************
          Lcd Inicialization
*****************************************/
void IR_Tire_System_UI::lcdIni(MCUFRIEND_kbv *tft_addr) {

  tft_ptr = tft_addr;

  uint16_t ID = tft_ptr->readID();
  tft_ptr->begin(ID);
  tft_ptr->setRotation(1);
  tft_ptr->fillScreen(BLACK);

  // Screen inicializations
  main_screen.iniScreen(tft_ptr);
  screen_select.iniScreen(tft_ptr);
  configuration_screen.iniScreen(tft_ptr);
  about_screen.iniScreen(tft_ptr);
  graph_screen.iniScreen(tft_ptr);
}

/********************************************
          Menu control method
*********************************************/

void IR_Tire_System_UI::menuControl(IR_Tire_System &sys, Input_buttons &input, unsigned long sys_time)
{
  switch (ui_main_menu_state)
  {
    /*******************
        MAIN SCREEN
     ******************/
    case 0:
        main_screen.displayScreen(sys,sys_time);

        // Transition
        if (input.ok_button.risingEdge()) {
          main_screen.resetState();
          ui_main_menu_state = 100;
        }

    break;
    /*******************
      MAIN MENU SCREEN
     ******************/
    case 100:

      screen_select.displayScreen(sys,sys_time,ui_screen_select_index);

      // Increment menu select index
      if (input.down_button.risingEdge()) {
        ui_screen_select_index++;
      }
      // Decrement menu select index
      if (input.up_button.risingEdge()) {
        ui_screen_select_index--;
      }
      // Menu selec idenx limits
      if (ui_screen_select_index > 3) {
        ui_screen_select_index = 0;
      }
      if (ui_screen_select_index < 0) {
        ui_screen_select_index = 3;
      }

      // Transition
      if (input.back_button.risingEdge()) {
        screen_select.resetState();
        ui_main_menu_state = 0;
        ui_screen_select_index = 0;
      } else if (input.ok_button.risingEdge()) {
        screen_select.resetState();
        ui_main_menu_state =  ui_screen_select_index;
        ui_screen_select_index = 0;
      }

    break;

    /***************************
        CONFIGURATION SCREEN
     **************************/
    case 1:

      // Increment menu select index
      if (input.down_button.risingEdge()) {
        ui_screen_select_index++;
      }
      // Decrement menu select index
      if (input.up_button.risingEdge()) {
        ui_screen_select_index--;
      }
      // Menu selec idenx limits
      if (ui_screen_select_index > 3) {
        ui_screen_select_index = 0;
      }
      if (ui_screen_select_index < 0) {
        ui_screen_select_index = 3;
      }

      if (input.ok_button.risingEdge()) {
        bool tmp;
        switch (ui_screen_select_index)
        {
          case 0:
            tmp  = sys.GetFrontSensorUsed();
            tmp = tmp^1;
            sys.SetFrontSensorUsed(tmp);
          break;
          case 1:
            tmp  = sys.GetRearSensorUsed();
            tmp = tmp^1;
            sys.SetRearSensorUsed(tmp);
          break;
          case 2:
            tmp  = sys.GetDataLoggingEnabled();
            tmp = tmp^1;
            sys.SetDataLoggingEnabled(tmp);
          break;
          case 3:
            sys.saveSettings();
            param_saved_tmp = true;
          break;
        }
      }

      configuration_screen.displayScreen(sys,sys_time,ui_screen_select_index);

      // Transition
      if (input.back_button.risingEdge() || param_saved_tmp) {
        configuration_screen.resetState();
        ui_main_menu_state = 100;
        ui_screen_select_index = 0;
        param_saved_tmp = false;
      }
    break;

    /***************************
            GRAPH SCREEN
    ****************************/
    case 2:
        graph_screen.displayScreen(sys,sys_time);

        // Transition
        if (input.ok_button.risingEdge()) {
          graph_screen.resetState();
          ui_main_menu_state = 100;
          ui_screen_select_index = 0;
          param_saved_tmp = false;
        }

    break;

    /***************************
         ABOUT SCREEN
     **************************/
    case 3:
      about_screen.displayScreen(sys,sys_time);

      // Transition
      if (input.back_button.risingEdge()) {
        about_screen.resetState();
        ui_main_menu_state = 100;
        ui_screen_select_index = 0;
        param_saved_tmp = false;
      }

    break;

  }
}
