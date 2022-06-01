#include <Arduino.h>
#include "UI_About_Screen.h"

void AboutScreen::iniScreen(MCUFRIEND_kbv *ptr)
{
  lcd = ptr;
}


void AboutScreen::displayScreen(IR_Tire_System &sys, unsigned long sys_time)
{
  if (!screen_displayed) {
    displayScreenCore();
    screen_displayed = true;
  }
}

void AboutScreen::displayScreenCore(void)
{
  lcd->fillScreen(BACKGROUND_COLOR);

  lcd->setTextSize(2);
  lcd->setTextColor(TEXT_COLOR);
  lcd->drawFastHLine(0,55,350,TEXT_COLOR);

  lcd->setCursor(20, 20);
  lcd->print("About");

  lcd->setCursor(20, 100);
  lcd->print("TIRE TEMPERATURE");
  lcd->setCursor(20, 140);
  lcd->print("MEASURING SYSTEM  v0.1");
  lcd->setCursor(20, 180);
  lcd->print("by M. Porenta");
}

void AboutScreen::resetState(void)
{
  screen_displayed = false;
  display_time = 0;
}
