#include <Arduino.h>
#include "UI_Main_Screen.h"
#include "Float_To_String.h"

void MainScreen::iniScreen(MCUFRIEND_kbv *ptr)
{
  lcd = ptr;
}

/****************************************
            Display Screen:
Main method for displaying screen on LCD
*****************************************/
void MainScreen::displayScreen(IR_Tire_System &sys, unsigned long sys_time)
{
  if (!screen_displayed) {
    checkSystemStatus(sys);
    displayScreenCore();
    screen_displayed = true;
  }

  if (sys_time - display_time > 1000){
    checkSystemStatus(sys);
    displayTemperature(sys);
    display_time = sys_time;

    displayAlert();
    alert_displayed = true;
  }
}

/****************************************
            Display Temperature
*****************************************/
void MainScreen::displayTemperature(IR_Tire_System &sys)
{
  float rear_temp;
  float front_temp;

  if (display_front) {
    front_temp = sys.GetFrontTemperature();
    displayTemperatureFront(front_temp);
  }
  if (display_rear) {
    rear_temp = sys.GetRearTemperature();
    displayTemperatureRear(rear_temp);
  }
}

/****************************************
            Check System Status
*****************************************/
void MainScreen::checkSystemStatus(IR_Tire_System &sys)
{
  bool front_en = sys.GetFrontSensorUsed();
  bool rear_en = sys.GetRearSensorUsed();
  bool front_comm = sys.GetFrontStatus();
  bool rear_comm = sys.GetRearStatus();
  data_logging_warrning = sys.GetDataLoggingEnabled();

  // Check if ok to display sensor values
  //Front
  if (front_en && front_comm) {
    display_front = true;
  } else {
    display_front = false;
  }
  //Rear
  if (rear_en && rear_comm) {
    display_rear = true;
  } else {
    display_rear = false;
  }

  // Check communication status of sesnors
  //Front
  if (front_en && !front_comm) {
    front_comm_warrning = true;
  } else {
    front_comm_warrning = false;
  }
  // Rear
  if (rear_en && !rear_comm) {
    rear_comm_warrning = true;
  } else {
    rear_comm_warrning = false;
  }
}

/****************************************
            Display Alert
*****************************************/
void MainScreen::displayAlert(void)
{
  lcd->setTextColor(TEXT_COLOR, BACKGROUND_COLOR);
  lcd->setCursor(20, 210);

  if (front_comm_warrning || rear_comm_warrning){
    lcd->setTextSize(2);
    lcd->print("COMMUNICATION ERROR!");
  }
  else if (data_logging_warrning)
  {
    lcd->setTextSize(2);
    lcd->print("LOGGING DATA");
  }
}

/****************************************
            Display Screen Core
*****************************************/
void MainScreen::displayScreenCore(void)
{

  lcd->fillScreen(BACKGROUND_COLOR);

  lcd->setTextSize(2);
  lcd->setTextColor(TEXT_COLOR);
  lcd->setCursor(20, 20);
  lcd->drawFastHLine(0,45,350,TEXT_COLOR);
  lcd->print("MAIN SCREEN");
  lcd->drawFastHLine(0,190,350,TEXT_COLOR);


  if(display_rear && display_front) {
    lcd->setTextSize(3.8);
    lcd->setCursor(3, 80);
    lcd->print("FRONT:");
    lcd->setCursor(20, 130);
    lcd->print("REAR: ");
  }

  if(display_rear && !display_front) {
    lcd->setTextSize(4);
    lcd->setCursor(20, 100);
    lcd->print("REAR: ");
  }

  if(!display_rear && display_front) {
    lcd->setTextSize(4);
    lcd->setCursor(3, 100);
    lcd->print("FRONT: ");
  }

  if(!display_rear && !display_front)
  {
    lcd->setTextSize(4);
    lcd->setCursor(20, 80);
    lcd->print("NO SENSORS");
    lcd->setCursor(20, 120);
    lcd->print("ENABLED!");
  }
}
/****************************************
        Display Temperature Rear
*****************************************/
void MainScreen::displayTemperatureRear(float temp)
{

  char tmp_str[20];
  ftoa(temp, tmp_str, 2);
  lcd->setTextColor(TEXT_COLOR, BACKGROUND_COLOR);

  // Display temperature

  if (display_front && display_rear) {
    // If both sensors enabled
    lcd->setTextSize(3.8);
    lcd->setCursor(130, 130);
    lcd->print(tmp_str);
    //Display units
    lcd->setCursor(225, 120);
    lcd->print((char)248);
    lcd->setCursor(240, 130);
    lcd->print('C');
  } else if (!display_front && display_rear) {
    // If one sensor enabled
    lcd->setTextSize(4);
    lcd->setCursor(140, 100);
    lcd->print(tmp_str);
    //Display units
    lcd->setCursor(256, 90);
    lcd->print((char)248);
    lcd->setCursor(278, 100);
    lcd->print('C');
  }
}

/****************************************
        Display Temperature Front
*****************************************/
void MainScreen::displayTemperatureFront(float temp)
{

  char tmp_str[20];
  ftoa(temp, tmp_str, 2);
  lcd->setTextColor(TEXT_COLOR, BACKGROUND_COLOR);

  if (display_front && display_rear) {
  // Display temperature
  lcd->setTextSize(3.8);
  lcd->setCursor(130, 80);
  lcd->print(tmp_str);

  //Display units
  lcd->setCursor(225, 70);
  lcd->print((char)248);
  lcd->setCursor(240, 80);
  lcd->print('C');

  } else if (display_front && !display_rear) {
    // If one sensor enabled
    lcd->setTextSize(4);
    lcd->setCursor(140, 100);
    lcd->print(tmp_str);
    //Display units
    lcd->setCursor(256, 90);
    lcd->print((char)248);
    lcd->setCursor(278, 100);
    lcd->print('C');
  }

}
/****************************************
        Reset Screen State
*****************************************/
void MainScreen::resetState(void)
{
  screen_displayed = false;
  alert_displayed = false;
  display_time = 0;
}
