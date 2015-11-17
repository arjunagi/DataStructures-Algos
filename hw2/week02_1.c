/*
 * Program to read an input from the keyboard and print out the 
 * characters in the input string without duplicates.
 * Ex: Input: hello how are you
 *     Output: helo waryu
 */

#include<stdio.h>
#include<string.h>

int main() {

  char inp[100],out[100]; //input and output arrays
  int i=0, j=0, k=0;
  int temp = 0;           // integer used as boolean flag
  printf("\nEnter the string ($ has to be the last character in the string):");
  gets(inp);

  for(i=0;i<strlen(inp);i++) {
      temp = 0;

      // break from the loop if the character is '$'
      if(inp[i] == '$')
          break;
      
      // Copy the first charac from input array to output array
      if(i == 0) {
          out[k] = inp[i];
          k++;
      }
      // For the rest of the charac in the inp array
      else {
          for(j=0;j<strlen(out);j++) {
              // if the current charac in the inp array matches any charac in the out array, set the flag and break from the loop
              if(inp[i] == out[j]) {
                  temp = 1;
                  break;
              }
          }//end of for(j)

          // if flag is not set, then there are no already copied duplicate characs in out array.
          // Hence, copy the charac to out array.
          if(temp != 1) {
              out[k] = inp[i];
              k++;
          }

      }// end of else

  } //end of for(i)

  printf("\nOutput: %s\n\n", out);
  
  return 0;
}
