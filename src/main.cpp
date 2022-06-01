#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <Wire.h>

#include "Mlx_Ir_sensor.h"
#include "IR_Tire_System.h"
#include "IR_Tire_System_UI.h"
#include "Button.h"
#include "Input_buttons.h"
#include "Float_To_String.h"

// Declare main objects
IR_Tire_System measuring_system;
IR_Tire_System_UI measuring_system_ui;
Input_buttons inputs;
MCUFRIEND_kbv lcd_display;

void setup()
{
  Serial.begin(9600);

  // Load system settings from eeprom
  measuring_system.readSysSettings();

  // Inicialize user interface
  measuring_system_ui.lcdIni(&lcd_display);

  // Inicialize measuring system
  measuring_system.begin();
  measuring_system.CheckComm();
  measuring_system.SetSamplingTime(500);
  measuring_system.SetDataLogInterval(500);
}

// Global time variable
unsigned long system_time = 0;

void loop()
{
  system_time = millis();

  // Collect temperature measurements
  measuring_system.measureTemp(system_time);

  // Log measurements to buffer
  //measuring_system.logData(system_time);

  // Refresh (control) user interface menu
  measuring_system_ui.menuControl(measuring_system, inputs,system_time);
}
