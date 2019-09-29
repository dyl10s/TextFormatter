#include "TextFormat.h"
#include <stdio.h>
#include <string.h>

//This function will load the next line
//from stdin with a max of 100 characters
char* LoadNextLine(char** output){
  return fgets(*output, 101, stdin);
}

//This function will print
//the buffer to stdout and format it correctly.
int PrintBuffer(char* buffer, int justified, int numSpaces, int lineLength){
  //If it is justified then
  //we need to format it/
  if(justified == 1){

    //Check how many spaces we have in the line
    int remainingSpace = lineLength - strlen(buffer) + numSpaces;
    int sizeOfSpace = remainingSpace / numSpaces;
    int charactersUsed = 0;

    //Loop through each character in the buffer
    for(int i = 0; i < strlen(buffer); i++){

      //if we have spaces left to delegate then
      //calculate what the size of a space should be
      if(numSpaces != 0){
        sizeOfSpace = (remainingSpace - charactersUsed) / numSpaces;
      }

      //If the current character is a space
      if(buffer[i] == ' '){
        float x;
        numSpaces--;
        //print to the screen the number of spaces
        //that we need to fill the line
        for(x = 0; x < sizeOfSpace; x++){
          printf(" ");
          charactersUsed++;
        }
      }else{
        //If the currect character is
        //not a space then just print it
        //to the screen.
        printf("%c", buffer[i]);
      }
    }
    //After we have looped through
    //all the characters print a new
    //line character.
    printf("\n");
  }else{
    //If the text is not justified
    //then just print the buffer followed by
    //a new line.
    printf("%s\n", buffer);
  }
  return 1;
}