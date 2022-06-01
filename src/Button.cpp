#include "Button.h"
#include <Arduino.h>


/****************************************
            Class Constructor
*****************************************/
Button::Button(int pin,int press_val, int release_val):input_pin{pin}, flag{false},
button_state{false}, button_state_raw{false}, debounce_press_val{press_val},
debounce_release_val{release_val}, press_ticks{0},release_ticks{0}, rising_edge{false},
falling_edge{false}
{
  pinMode(pin,OUTPUT);
}

/****************************************
            Set debounce parameters
*****************************************/
void Button::setDebounceFilter(int press_val, int release_val)
{
  if (press_val > 1) {
  debounce_press_val = press_val;
} else {
  debounce_press_val = 1;
}

  if (release_val > 1) {
    debounce_release_val = release_val;
  } else {
    debounce_release_val = 1;
  }
}

/****************************************
            Debounce button filter
*****************************************/
bool Button::buttonDebounce(void)
{
  bool input_val = digitalRead(input_pin);

  // Button press
  if (input_val && !button_state)
  {
    press_ticks++;
    if (press_ticks >= debounce_press_val)
    {
      button_state = true;
      press_ticks = 0;
    }
  }
  else if (!input_val && button_state)
  {
    release_ticks++;
    if (release_ticks >= debounce_release_val)
    {
      button_state = false;
      release_ticks = 0;
    }
  }
  return button_state;

}

/****************************************
          Return Button State
*****************************************/
bool Button::getButtonState(String mode)
{
  return button_state;
}


/****************************************
          Detect rising edge
*****************************************/
bool Button::risingEdge(void)
{
  bool tmp = buttonDebounce();
  if (tmp)
  {
    //Detecting Rising Edge
    if (!rising_edge && !flag)
    {
       rising_edge = true;
    }
    else
    {
      rising_edge = false;
      flag = true;
    }
  }
  else
  {
      rising_edge = false;
      flag = false;
  }
  return rising_edge;
}
