#include <Arduino.h>
#include "UI_Configuration_Screen.h"

void ConfigurationScreen::iniScreen(MCUFRIEND_kbv *ptr)
{
  lcd = ptr;
}
void ConfigurationScreen::displayScreen(IR_Tire_System &sys, unsigned long sys_time, int menu_num)
{

  // Get system status
  bool front_en_new = sys.GetFrontSensorUsed();
  bool rear_en_new =  sys.GetRearSensorUsed();
  bool enable_data_logging_new = sys.GetDataLoggingEnabled();

  if (!screen_displayed) {
    front_en = front_en_new;
    rear_en = rear_en_new;
    enable_data_logging = enable_data_logging_new;

    displayScreenCore();
    displayParamVal();
    screen_displayed = true;
  }
  if (selected_menu != menu_num){
    moveSelector(menu_num);
    selected_menu = menu_num;
  }

  if (front_en_new != front_en || rear_en_new != rear_en || enable_data_logging_new
  != enable_data_logging) {
    front_en = front_en_new;
    rear_en = rear_en_new;
    enable_data_logging = enable_data_logging_new;
    displayParamVal();
  }
}

void ConfigurationScreen::moveSelector(int pos)
{
  lcd->drawRect(9,menu_selector_pos[previouse_selected_menu],300,40,BACKGROUND_COLOR);
  lcd->drawRect(9,menu_selector_pos[pos],300,40,TEXT_COLOR);
  previouse_selected_menu = pos;
}

void ConfigurationScreen::displayScreenCore(void)
{
  lcd->fillScreen(BACKGROUND_COLOR);

  lcd->setTextSize(2);
  lcd->setTextColor(TEXT_COLOR);
  lcd->drawFastHLine(0,55,350,TEXT_COLOR);

  //Display screen name
  lcd->setCursor(20, 20);
  lcd->print("CONFIGURATION");

  //Dsiplay configuration menu
  lcd->setCursor(14, 85);
  lcd->print("Front sensor enable=");

  lcd->setCursor(30, 125);
  lcd->print("Rear sensor enable=");

  lcd->setCursor(30, 165);
  lcd->print("Enable  logging =");

  lcd->setCursor(30, 200);
  lcd->print("Save configuration");
}

void ConfigurationScreen::displayParamVal(void)
{
    lcd->setTextColor(TEXT_COLOR, BACKGROUND_COLOR);

    // Fron sensor enalbed status
    lcd->setCursor(270, 85);
    lcd->print(front_en);
    // Rear sensor enabled status
    lcd->setCursor(270, 125);
    lcd->print(rear_en);

    //Data logging enabled
    lcd->setCursor(270, 165);
    lcd->print(enable_data_logging);
}

void ConfigurationScreen::resetState(void)
{
  screen_displayed = false;
  display_time = 0;
  selected_menu = 66;
}
