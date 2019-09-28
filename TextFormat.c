#include "TextFormat.h"
#include <stdio.h>

char* LoadNextLine(char** output){
  return fgets(*output, 101, stdin);
}