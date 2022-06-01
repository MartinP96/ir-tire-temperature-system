#include <Arduino.h>
#include "UI_Screen_Select.h"


void ScreenSelect::iniScreen(MCUFRIEND_kbv *ptr)
{
  lcd = ptr;
}

void ScreenSelect::displayScreen(IR_Tire_System &sys, unsigned long sys_time, int menu_num)
{
  if (!screen_displayed) {
    displayScreenCore();
    screen_displayed = true;
  }
  if (selected_menu != menu_num){
    moveSelector(menu_num);
    selected_menu = menu_num;
  }
}

void ScreenSelect::moveSelector(int pos)
{
  lcd->drawRect(55,menu_selector_pos[previouse_selected_menu],180,40,BACKGROUND_COLOR);
  lcd->drawRect(55,menu_selector_pos[pos],180,40,TEXT_COLOR);
  previouse_selected_menu = pos;
}

void ScreenSelect::displayScreenCore(void)
{
  lcd->fillScreen(BACKGROUND_COLOR);

  lcd->setTextSize(2);
  lcd->setTextColor(TEXT_COLOR);
  lcd->drawFastHLine(0,55,350,TEXT_COLOR);

  lcd->setCursor(20, 20);
  lcd->print("MAIN MENU");

  lcd->setCursor(60, 85);
  lcd->print("MAIN SCREEN");

  lcd->setCursor(60, 125);
  lcd->print("CONFIGURATION");

  lcd->setCursor(60, 165);
    lcd->print("DATA GRAPH");

  lcd->setCursor(60, 205);
  lcd->print("ABOUT");
}

void ScreenSelect::resetState(void)
{
  screen_displayed = false;
  display_time = 0;
  selected_menu = 66;
}
