#ifndef _UI_GRAPH_SCREEN_H_
#define _UI_GRAPH_SCREEN_H_

#include <Arduino.h>
#include "IR_Tire_System.h"
#include "Float_To_String.h"
#include <MCUFRIEND_kbv.h>
#include "UI_Colors.h"

#define GRAPH_X_AXIS_LEN  250
#define GRAPH_Y_AXIS_LEN  190
#define GRAPH_ZERO_POS_X  40
#define GRAPH_ZERO_POS_Y  195

#define GRAPH_X_AXIS_NUM_OF_DIVISIONS 10

class GraphScreen
{
public:

  GraphScreen():screen_displayed{false}, display_time{0} {
  }

  void iniScreen(MCUFRIEND_kbv *ptr);
  void displayScreen(IR_Tire_System &sys, unsigned long sys_time);
  void resetState(void);

private:

  // Variables
  MCUFRIEND_kbv *lcd;
  bool screen_displayed;
  unsigned long display_time;

  // Methods
  void setXAxis(float max_value);
  void setYAxis(int max_value);
  void displayScreenCore(void);
  void plotGraph(CircuralBuffer<float> &data);
  float getMaxValue(float data[], int data_len);
  float getMinValue(float data[], int data_len);

};

#endif
