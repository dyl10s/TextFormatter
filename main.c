/*
Dylan Strohschein
CIS 343-02
This program will print the input text
with a max width with the parameter -w
if the parameter -j is used all lines will
be justified to the same width if its not
the last line of a paragraph
*/

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

    //If there is a j as the argument we need to get the number after it and
    //set justified equal to 1
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

  //If there was no w or j value throw an error
  if(foundLegthValue == 0)
  {
    fprintf (stderr, "You must specify a -w or -j value");
    return -1;
  }

  //If there was both a w and j value throw an error
  if(foundLegthValue == 2)
  {
    fprintf (stderr, "You must not specify both a -w and -j value");
    return -1;
  }

  //Set up the current line to handle a max of a 100 character line
  char *curLine;
  curLine = (char*) malloc(101 * sizeof(char));

  //Setup our buffer to be able to hold a string as long as the specified line length
  char *buffer;
  buffer = (char*) malloc((lineLength + 1) * sizeof(char));
  strcpy(buffer, "");

  int curLineLength = 0;
  int isFirstInLine = 1;

  int overflowLines = 0;
  int spacesInLine = 0;

  //While there is another line coming from stdin
  while (LoadNextLine(&curLine))
  {
    //If the line just equals a new line then we know
    //this is the end of a paragraph
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
      //Split the current line by space and new line and loop
      //through each word.
      char *curWord = strtok(curLine, " \n");
      while (curWord != NULL)
      {
        //If the word can fit in the current line then 
        //we will add it to the current buffer
        if(
            (isFirstInLine == 1 && 
            curLineLength + strlen(curWord) <= lineLength) 
            || 
            (isFirstInLine == 0 && 
            curLineLength + strlen(curWord) + 1 <= lineLength)
          ){
          
          //If the word is not the first in
          //the line then we need to put a 
          //space before it
          if(isFirstInLine == 0){
            buffer = strcat(buffer, " ");
            spacesInLine++;
            curLineLength += 1;
          }else{
            isFirstInLine = 0;
          }

          //Add the current word to the buffer and update the
          //current lines length
          curLineLength += strlen(curWord);
          buffer = strcat(buffer, curWord);
        }else{
          //If the next word will not fit on the current
          //line then we need to print the buffer
          //to the screen and clear it
          PrintBuffer(buffer, justified, spacesInLine, lineLength);
          spacesInLine = 0;
          strcpy(buffer, "");
          curLineLength = strlen(curWord);

          //If we can not fit the current word on
          //its own line then we have an overflow error.
          if(curLineLength >= lineLength){
            overflowLines++;
            printf("%s", curWord);
          }else{
            strcpy(buffer, curWord);
          }
        }

        //Move to the next word in the line
        curWord = strtok(NULL, " \n");
      }
    }
  }

  //After we have gone through all the words we
  //need to print the rest of the buffer
  //to the screen. It is an incomplete
  //line so we dont need any formatting.
  printf("%s", buffer);

  //If there were any overflow lines
  //tell the user.
  if(overflowLines > 0){
    fprintf (stderr, "\n\nWarning: %d overfull line(s)", overflowLines);
  }

  //Release the pointers.
  free(curLine);
  free(buffer);

  return 1;
}