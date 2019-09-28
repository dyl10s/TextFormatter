#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TextFormat.h"

int main(int argc, char *argv[])
{

  int lineLength = 0;
  int foundWValue = 0;

  // Start off by parsing the command line arg for lineLength
  for (int i = 1; i < argc; i++)
  {
    if (strcmp(argv[i], "-w") == 0)
    {
      if (i + 1 < argc)
      {
        foundWValue = 1;
        lineLength = atoi(argv[i + 1]);
      }
      else
      {
        printf("Please specifiy a length after -w");
      }
    }
  }

  if(foundWValue == 0)
  {
    fprintf (stderr, "You must specify a -w value");
    return -1;
  }

  char *curLine;
  curLine = (char *)malloc(101 * sizeof(char));
  int curLineLength = 0;
  int isFirstInLine = 1;

  int overflowLines = 0;

  while (LoadNextLine(&curLine))
  {
    if (strcmp(curLine, "\n") == 0)
    {
      printf("\n\n");
      isFirstInLine = 1;
      curLineLength = 0;
    }
    else
    {
      char *curWord = strtok(curLine, " \n");
      while (curWord != NULL)
      {
        if((isFirstInLine == 1 && curLineLength + strlen(curWord) <= lineLength) 
        || (isFirstInLine == 0 && curLineLength + strlen(curWord) + 1 <= lineLength)){
          
          if(isFirstInLine == 0){
            printf(" ");
            curLineLength += 1;
          }else{
            isFirstInLine = 0;
          }

          curLineLength += strlen(curWord);
          printf("%s", curWord); 
        }else{
          printf("\n");
          curLineLength = strlen(curWord);
          if(curLineLength >= lineLength){
            //Overflow Error
            overflowLines++;
            printf("%s", curWord);
          }else{
            printf("%s", curWord);
          }
        }
        curWord = strtok(NULL, " \n");
      }
    }
  }

  if(overflowLines > 0){
    fprintf (stderr, "\n\nWarning: %d overfull line(s)", overflowLines);
  }

  free(curLine);

  return 0;
}