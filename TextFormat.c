#include "TextFormat.h"
#include <stdio.h>
#include <string.h>

char* LoadNextLine(char** output){
  return fgets(*output, 101, stdin);
}

int PrintBuffer(char* buffer, int justified, int numSpaces, int lineLength){
  if(justified == 1){

    int remainingSpace = lineLength - strlen(buffer) + numSpaces;
    int sizeOfSpace = remainingSpace / numSpaces;
    int charactersUsed = 0;

    for(int i = 0; i < strlen(buffer); i++){
      if(numSpaces != 0){
        sizeOfSpace = (remainingSpace - charactersUsed) / numSpaces;
      }
      if(buffer[i] == ' '){
        float x;
        numSpaces--;
        for(x = 0; x < sizeOfSpace; x++){
          printf(" ");
          charactersUsed++;
        }
      }else{
        printf("%c", buffer[i]);
      }
    }

    printf("\n");
  }else{
    printf("%s\n", buffer);
  }
  return 1;
}