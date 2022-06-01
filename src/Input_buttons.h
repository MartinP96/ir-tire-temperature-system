#ifndef _INPUT_BUTTONS_H_
#define _INPUT_BUTTONS_H_
#include "Button.h"

#define OK_BTN_PIN        PB12
#define UP_BUTTON_PIN     PB13
#define DOWN_BUTTON_PIN   PB14
#define BACK_BUTTON_PIN   PB15

#define PRESS_THRES       100
#define RELEASE_THRES     100


class Input_buttons
{
public:

  //Constructor
  Input_buttons(): ok_button(OK_BTN_PIN,PRESS_THRES,RELEASE_THRES),
  up_button(UP_BUTTON_PIN,PRESS_THRES,RELEASE_THRES),
  down_button(DOWN_BUTTON_PIN,PRESS_THRES,RELEASE_THRES),
  back_button(BACK_BUTTON_PIN,PRESS_THRES,RELEASE_THRES) {}
  // End of contructor

  Button ok_button;
  Button up_button;
  Button down_button;
  Button back_button;
};

#endif
