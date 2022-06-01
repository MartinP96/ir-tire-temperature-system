#ifndef _FLOAT_TO_STRING_H_
#define _FLOAT_TO_STRING_H_

#include <Arduino.h>

/*
FUNKCIJA ZA PRETVORBO FLOAT V STRING

Primer uporabe:

  char res[20];
  float n = 22.31;
  ftoa1(n, res, 1);

res - izhodni string
n - vhodni float
'1' - število cifer po decimalni vejici

*/

void reverse(char* str, int len);

// Converts a given integer x to string str[].
// d is the number of digits required in the output.
// If d is more than the number of digits in x,
// then 0s are added at the beginning.
int intToStr(int x, char str[], int d);


// Converts a floating-point/double number to a string.
void ftoa(float n, char* res, int afterpoint);


#endif
