#ifndef PARSE_INT_H
#define PARSE_INT_H

#include <math.h>
#include <string.h>
#include <stdbool.h>


static int parse_int(char* str) {
  int result = 0;

  bool negative = false;
  if (*str == '-') {
    str++;
    negative = true;
  }
  
  int idx = strlen(str) - 1;
  while (*str != '\0') {
    char digit = (*str) - 48;
    result += digit * pow(10, idx);

    idx--;
    str++;
  }

  if (negative) result = ~result + 1; // CS:APP FOR THE WINNNN
  return result;
}


#endif /* PARSE_INT_H */
