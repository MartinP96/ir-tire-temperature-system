#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <Arduino.h>
class Button
{
public:
  // Contructor
  Button(int pin, int press_val = 1, int release_val = 1);

  bool fallingEdge(void);
  bool risingEdge(void);

  void setDebounceFilter(int press_val, int release_val);
  bool getButtonState(String mode);

private:

  bool buttonDebounce(void);
  
  int input_pin;
  bool flag;
  bool button_state;
  bool button_state_raw;
  int debounce_press_val;
  int debounce_release_val;
  int press_ticks;
  int release_ticks;
  bool rising_edge;
  bool falling_edge;
};

#endif
