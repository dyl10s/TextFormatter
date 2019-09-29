#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TextFormat.h"

int main(int argc, char *argv[])
{

  int lineLength = 0;
  int foundLegthValue = 0;
  int justified = 0;

  // Start off by parsing the command line arg for lineLength
  for (int i = 1; i < argc; i++)
  {
    if (strcmp(argv[i], "-w") == 0)
    {
      if (i + 1 < argc)
      {
        foundLegthValue += 1;
        lineLength = atoi(argv[i + 1]);
      }
      else
      {
        printf("Please specifiy a length after -w");
      }
    }

    if (strcmp(argv[i], "-j") == 0)
    {
      if (i + 1 < argc)
      {
        justified = 1;
        foundLegthValue += 1;
        lineLength = atoi(argv[i + 1]);
      }
      else
      {
        printf("Please specifiy a length after -j");
      }
    }
  }

  if(foundLegthValue == 0)
  {
    fprintf (stderr, "You must specify a -w or -j value");
    return -1;
  }

  if(foundLegthValue == 2)
  {
    fprintf (stderr, "You must not specify both a -w and -j value");
    return -1;
  }

  char *curLine;
  curLine = (char*) malloc(101 * sizeof(char));

  char *buffer;
  buffer = (char*) malloc((lineLength + 1) * sizeof(char));
  strcpy(buffer, "");

  int curLineLength = 0;
  int isFirstInLine = 1;

  int overflowLines = 0;
  int spacesInLine = 0;

  while (LoadNextLine(&curLine))
  {
    if (strcmp(curLine, "\n") == 0)
    {
      printf("%s", buffer);
      strcpy(buffer, "");
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
            buffer = strcat(buffer, " ");
            spacesInLine++;
            curLineLength += 1;
          }else{
            isFirstInLine = 0;
          }

          curLineLength += strlen(curWord);
          buffer = strcat(buffer, curWord);
        }else{
          PrintBuffer(buffer, justified, spacesInLine, lineLength);
          spacesInLine = 0;
          strcpy(buffer, "");
          curLineLength = strlen(curWord);
          if(curLineLength >= lineLength){
            //Overflow Error
            overflowLines++;
            printf("%s", curWord);
          }else{
            strcpy(buffer, curWord);
          }
        }
        curWord = strtok(NULL, " \n");
      }
    }
  }

  printf("%s", buffer);

  if(overflowLines > 0){
    fprintf (stderr, "\n\nWarning: %d overfull line(s)", overflowLines);
  }

  free(curLine);
  free(buffer);

  return 0;
}