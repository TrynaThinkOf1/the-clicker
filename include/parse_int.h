#ifndef PARSE_INT_H
#define PARSE_INT_H

#include <math.h>
#include <string.h>
#include <stdbool.h>


static int parse_int(const char* str, int len) {
  int result = 0;

  int idx = 0;
  for (char* c = str + len; c >= str; c--) {
   	result += (*c - 48) * pow(10, idx);
   	idx++;
  }

  return result;
}


#endif /* PARSE_INT_H */
