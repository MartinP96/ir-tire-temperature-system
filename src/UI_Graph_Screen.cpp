#include "UI_Graph_Screen.h"
#include <Arduino.h>
#include <String.h>
#include <math.h>
#include "Float_To_String.h"

/******************************************************
                Screen inicialization
*******************************************************/
void GraphScreen::iniScreen(MCUFRIEND_kbv *ptr)
{
  lcd = ptr;
}

/******************************************************
                Display screen public method
*******************************************************/
void GraphScreen::displayScreen(IR_Tire_System &sys, unsigned long sys_time)
{
  if (!screen_displayed) {
    displayScreenCore();
    screen_displayed = true;
  }
  if (sys.dataBuffer.isBufferFull())
  {
    plotGraph(sys.dataBuffer);
  }
}

/******************************************************
      Display screen core (static screen features)
*******************************************************/
void GraphScreen::displayScreenCore(void)
{
  // Dsiplay graph core
  lcd->fillScreen(BACKGROUND_COLOR);
  lcd->drawFastHLine(GRAPH_ZERO_POS_X,GRAPH_ZERO_POS_Y,
    GRAPH_X_AXIS_LEN,TEXT_COLOR);
  lcd->drawFastVLine(GRAPH_ZERO_POS_X,GRAPH_ZERO_POS_Y,
    -GRAPH_Y_AXIS_LEN,TEXT_COLOR);


  // Display Y axis
  int y_div = GRAPH_Y_AXIS_LEN/10;
  int current_div_y = GRAPH_ZERO_POS_Y;
  for (int i = 0; i < 10; i++)
  {
    lcd->drawFastHLine(GRAPH_ZERO_POS_X,current_div_y,10,TEXT_COLOR);

    if (i > 0)
    {
      lcd->setTextSize(1);
      lcd->setCursor(GRAPH_ZERO_POS_X-15,current_div_y );
      lcd->print(i);
    }
    current_div_y = current_div_y - y_div;
  }
}

/******************************************************
      Display screen core (static screen features)
*******************************************************/
void GraphScreen::plotGraph(CircuralBuffer<float> &data)
{
  float tmp;
  float tmp2;

  // First two data points
  data.readFromBuffer(&tmp);
  data.readFromBuffer(&tmp2);

  for (int i = 0; i < data.getBufferSize()-1; i++)
  {
    if (i > 0)
    {
      tmp = tmp2;
      data.readFromBuffer(&tmp2);
    }

    int mapped_y = map(tmp*10,0,500,225,5);
    int mapped_x = map(i*10,0,990,0,300);

    int mapped_y2 = map(tmp2*10,0,500,225,5);
    int mapped_x2 = map((i+1)*10,0,990,0,300);

    Serial.print("(");
    Serial.print(mapped_x);
    Serial.print(",");
    Serial.print(mapped_y);
    Serial.print("), (");
    Serial.print(mapped_x2);
    Serial.print(",");
    Serial.print(mapped_y2);
    Serial.println(")");

    lcd->drawLine(mapped_x, mapped_y, mapped_x2, mapped_y2,TEXT_COLOR);

    //Serial.print(mapped_x);
    //Serial.print(',');
    //Serial.println(mapped_y);
    //lcd->drawPixel(mapped_x,mapped_y,TEXT_COLOR);

  }
}

void GraphScreen::setXAxis(float max_vlaue)
{
  // Display X axis
  int x_div = GRAPH_X_AXIS_LEN/GRAPH_X_AXIS_NUM_OF_DIVISIONS;
  int current_div = GRAPH_ZERO_POS_X;
  float division_label = 0;

  for (int i = 0; i < GRAPH_X_AXIS_NUM_OF_DIVISIONS; i++)
  {
    lcd->drawFastVLine(current_div,GRAPH_ZERO_POS_Y,-10,TEXT_COLOR);



    lcd->setTextSize(1);
    lcd->setCursor(current_div, GRAPH_ZERO_POS_Y+10);
    lcd->print(i);
    current_div = current_div + x_div;
  }
  lcd->setCursor(GRAPH_X_AXIS_LEN+GRAPH_ZERO_POS_X, GRAPH_ZERO_POS_Y+10);
  lcd->print("[s]");
}


/******************************************************
            Find max value in data array
*******************************************************/
float GraphScreen::getMaxValue(float data[], int data_len)
{
  float max_val = 0;

  for (int i = 0; i < data_len; i++)
  {
    if (data[i] > max_val)
    {
      max_val = data[i];
    }
  }
  return max_val;
}

/******************************************************
            Find min value in data array
*******************************************************/
float GraphScreen::getMinValue(float data[], int data_len)
{
  float min_val = 500000;

  for (int i = 0; i < data_len; i++)
  {
    if (data[i] < min_val)
    {
      min_val = data[i];
    }
  }
  return min_val;
}

/******************************************************
              Reset inner states
*******************************************************/

void GraphScreen::resetState(void)
{
  screen_displayed = false;
  display_time = 0;
}
