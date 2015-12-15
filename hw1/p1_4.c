#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  MAX_LENGTH 21 //it is 21 to account for the NULL character at the end

int main(int args, char *argv[])
{
  //open the file
  FILE *fp; //file pointer
  char word[MAX_LENGTH]; // will hold a word
  char c; //to check for end of file

  //check for the apporpiate number of files
  if(args !=3)
  {
    printf("not the correctt number of arguments were give, just provided inut and output file locations\n");
    exit(0);
  }

  //open the file
  fp = fopen(argv[1],"r");
  if (fp == NULL)
  {
    printf("error while opening file");
    exit(0);
  }

  //get character by word on the file
  int n =0 ;
  while ((c = fgetc(fp)) != EOF) 
  {
          if((c >=65 && c<=90) || (c>=97 && c<=122) || (c>=48 && c<=57))
          {
            word[n] = (char) c;
            n++;
          }
          else
          {
            if(n!=0)
            {
             int len = strlen(word);
             char reversed[len+1];
             for(int i=0; i<len;i++)
             {
               //printf("%c",word[i]);
               reversed[i]=word[len-i-1];
               word[len-i]=0;
             }
              reversed[len]=0;
              printf("%s",reversed);
              n=0;
            }
            printf("%c",(char) c);
          }
  }

     fclose(fp);
}
