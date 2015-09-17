/*
 Read a positive integer from the keyboard and print the out digit by digit as words.
 Ex: 1 = one
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void) {

  int n,rem,len,i;
  char intAsString[10]; //integer as a char array. Ex: 1234 = [1,2,3,4]
  char intToWord[100]; //each digit of an int stored as an English word. Ex: 1=one
  printf("\nEnter a number (max value of 32767 for 16bit and 2147483647 for 32/64bit compilers):");
  scanf("%d", &n);
  len = sprintf(intAsString,"%d",n); //copies the integer to a char array and returns the number of characters copied.

  for(i=0; i<len; i++) {
    switch(intAsString[i]) {
      case '0': strcat(intToWord,"zero ");
                break;
      case '1': strcat(intToWord,"one ");
                break;
      case '2': strcat(intToWord,"two ");
                break;
      case '3': strcat(intToWord,"three ");
                break;
      case '4': strcat(intToWord,"four ");
                break;
      case '5': strcat(intToWord,"five ");
                break;
      case '6': strcat(intToWord,"six ");
                break;
      case '7': strcat(intToWord,"seven ");
                break;
      case '8': strcat(intToWord,"eight ");
                break;
      case '9': strcat(intToWord,"nine ");
                break;
    }
  }

  printf("\nOutput: %s\n",intToWord);

  return 0;
}

