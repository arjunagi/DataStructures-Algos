#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
   argc - number of total arguments, i.e number of argv array elements
   argv - array of arguments
          argv[0] - a.out
          argv[1] - option_number
          argv[2],argv[3],argv[4] - files on which operations have to be performed
 */
int main(int argc, char *argv[]) {
 
  /*
     If the number of arguments is less than 3(a.out option_number file), print error and exit
   */ 
  if(argc<3) {
    printf("\nWrong number of options provided for a.out\n");
    printf("\nThe usage menu is as below:\n");
    printf("Copy:       a.out 0 file1.txt file2.txt\n");
    printf("Interleave: a.out 1 file.txt file2.txt file3.txt\n");
    printf("More:       a.out 2 file1.txt\n");
    printf("Grep:       a.out 3 file1.txt\n");
    printf("Word Count: a.out 4 file1.txt\n");
    exit(0); 
  }

  /*
     If the first argument,i.e the option_number is not between 0 and 4, print error and exit
   */
  if(!(0<=atoi(argv[1]) || atoi(argv[1])<=4))
  {
    printf("First option provided for a.out is illegal. It should be between 0 and 4.");
    exit(0);
  }

  /*
     Files to be operated on
   */
  FILE * in = NULL;  //Option 0,2,3,4
  FILE * in1 = NULL; //Option 1
  FILE * in2 = NULL; //Option 1
  FILE * out = NULL; //Option 0,1

  /*
     Check if the number of arguments is correct according to the option_number
     Ex: For Copy operation(option_number=0), there are 4 arguments: a.out 0 file1.txt file2.txt
   */
  if((argc==4) && (atoi(argv[1])==0)) {
    in = fopen(argv[2], "r");
    out = fopen(argv[3], "w");
  }
  else if((argc==5) && (atoi(argv[1])==1)) {
    in1 = fopen(argv[2], "r");
    in2 = fopen(argv[3], "r");
    out = fopen(argv[4], "w");
  }
  else if((argc==3) && ((atoi(argv[1])==2) || (atoi(argv[1])==3) || (atoi(argv[1])==4))) {
    in = fopen(argv[2], "r");
  }
  else {
    printf("\nWrong options provided for a.out\n");
    printf("\nThe usage menu is as below:\n");
    printf("Copy:       a.out 0 file1.txt file2.txt\n");
    printf("Interleave: a.out 1 file.txt file2.txt file3.txt\n");
    printf("More:       a.out 2 file1.txt\n");
    printf("Grep:       a.out 3 file1.txt\n");
    printf("Word Count: a.out 4 file1.txt\n");
    exit(0);
  }

  /*
     Check if the number of files is correct with respect to the option_number
   */
  if(((atoi(argv[1])==0) || (atoi(argv[1])==2) || (atoi(argv[1])==3) || (atoi(argv[1])==4)) && (in==NULL)) {
    printf("\nError opening file %s.\n",argv[2]);
    exit(0);
  }
  else if((atoi(argv[1])==0) && (out==NULL)) {
    printf("\nError opening file %s.\n",argv[3]);
    exit(0);
  }
  else if(atoi(argv[1])==1 ) {
    if(in1==NULL) {
      printf("\nError opening file %s.\n",argv[2]);
      exit(0);
    }
    if(in2==NULL) {
      printf("\nError opening file %s.\n",argv[3]);
      exit(0);
    }
    if(out==NULL) {
      printf("\nError opening file %s.\n",argv[4]);
      exit(0);
    }
  }

  // case 0 - Copying files
  char ch[100];

  // case 1 - Interleave
  char line1[200], line2[200];
  char *c1, *c2;

  // case 2 - more
  int i=0;
  char userInp='p';
  char readLines[200], *temp = NULL;

  // case 3 - grep
  char grepWord[11], oneWord[500];
  int grepWordLen = 0, lineNum = 1;

  // case 4 - Word count
  char * line[100];  // to store all the lines in the file
  char tempWord[30], tempLine[200];  // temporary array to store a word
  char *c, *prev, *tempChar;    
  char longestWord1[30], longestWord2[30], longestWord3[30];
  int wordsInLine = 0, shortestLineWords = 0; //number of words in line and length of shortest line in terms of words
  int longestWordsLen[3] = {0,0,0}; //lengths of longest words
  int j = 1,k = 0;
  int lineNumChars = 0, lineNumWords = 0; //line number of shortest lines in terms of characs and words
  int lines=0,words=0,chars=0;  // Number of lines, words and characters in the file
  int shortestLineLen = 0, lineLen = 0; // Length of shortest line in terms of length, size of a read line


  switch (argv[1][0]) {
  
   /*
    * Copying files
    */
   case'0':
       // Get a character from the input file and put it in the out file
       while(fgets(ch,100,in) != NULL)
           fprintf(out,"%s", ch);

       fclose(out);
       fclose(in);
       break;
       //End of case '0'


   /*
    * Interleave
    */
   case'1':
       do {
           // read line from file 1 and put it in out file
           if((c1 = fgets (line1, 200, in1))!=NULL) {
               fprintf(out,"%s",line1);
           }

           // read line from file 2 and put it in out file
           if((c2 = fgets (line2, 200, in2))!=NULL) {
               fprintf(out,"%s",line2);
           }
       } while((c1 != NULL) || (c2 != NULL));

       fclose(in1);
       fclose(in2);
       fclose(out);
       break;
       //End of case '1'

   
   /*  
    * more
    * Print first 10 lines from a file and wait for user input
    * if userInp is 'p', print next 10 lines
    * if userInp is 'n', print next line
    * if userInp is 'q', quit
    */
   case '2':
       do {
           if(userInp=='p') {
               //Read 10 lines from file and print it
               for(i=0;i<10;i++) {
                   temp = fgets(readLines, 200, in);
                   if(temp != NULL)
                       printf("%s",readLines);
                   else
                       exit(0);
               } // end of for
           } // end of if

           else if(userInp=='n') {
               // Read the next line and print it
               temp = fgets(readLines, 200, in);
               if(temp != NULL)
                   printf("%s", readLines);
               else
                   exit(0);
           } // end of else if

           scanf("%c",&userInp); // take input from user for the next action
       } while((userInp!='q') || (userInp=='n') || (userInp=='p'));

       fclose(in);
       break;
       //End of case '2'


  /*
   * grep - case sensitive
   */
  case '3':
      printf("\nInput search string (10 char max): ");
      fgets (grepWord, 11, stdin); //get the search string. Length is 11 as fgets read \n also.
      grepWordLen = strlen(grepWord);
      
      //Change the last character of the word to '\0' to make it string compatible
      if ((grepWordLen>0) && (grepWord[grepWordLen - 1] == '\n'))
          grepWord[grepWordLen - 1] = '\0';

      // Word to be searched has to be max 10 characters
      if(grepWordLen <= 10) {
          // Get each line from the file and see the word is a substring in the line. If yes, then print the line
          while((fgets(oneWord,500,in)) != NULL) {
              if((strstr(oneWord,grepWord)) != NULL ) {
                  printf("\nline %d: %s",lineNum,oneWord);
              }
              lineNum+=1;
          } // end of while
      } // end of if
      else {
          printf("\n Search string should be 10 characters max");
          exit(0);
      }

      fclose(in);
      break;
      //End of case '3'
  

    /*
     * Word count
     */ 
    case '4':
        // read the file line by line
        while ((tempChar = fgets(tempLine, 200, in)) != NULL) {

            lineLen = strlen(tempLine);
            line[j] = malloc(lineLen + 1);
            strcpy(line[j],tempLine);

            // Get the shortest line in the file in terms of characters
            if(shortestLineLen == 0 || lineLen < shortestLineLen) {
                shortestLineLen = lineLen;
                lineNumChars = j; //Get the line number of the lines
            } //end of if

            c = line[j]; //point to first character of each line
            wordsInLine = 0;

            do { 
                // Read the line character by character to get number of words in a line 
                if((*c>='0' && *c<='9') || (*c>='a' && *c<='z') || (*c>='A' && *c<='Z')) {
                    tempWord[k] = *c; // store the word character by character
                    ++k;
                }
                else {
                    tempWord[k] = '\0'; // add '\0' at end of each word to make it string compatible

                    // Get the 3 longest words in the file
                    if(strlen(tempWord) > longestWordsLen[0]) {
                        longestWordsLen[0] = strlen(tempWord);
                        strcpy(longestWord1, tempWord);
                    }  
                    else if(strlen(tempWord) > longestWordsLen[1]) {
                       longestWordsLen[1] = strlen(tempWord);
                       strcpy(longestWord2, tempWord);
                    }
                    else if(strlen(tempWord) > longestWordsLen[2]) {
                       longestWordsLen[2] = strlen(tempWord);
                       strcpy(longestWord3, tempWord);
                    }
                
                    memset(tempWord,'\0',30); //Reset the tempWord array so that next word can be stored
                    k = 0;
                     
                    // Count the number of words in a line only if the previous character was alphanumeric  and current character is not alphanumeric
                    if((*prev>='0' && *prev<='9') || (*prev>='a' && *prev<='z') || (*prev>='A' && *prev<='Z')) {
                        wordsInLine++;
                    }
                }//end of else
  
                prev = c; //store the current character before moving onto the next character
                chars++; // increment the character count
                c++; // move to the next character in the line 
            } while (*c != '\n');
            // end of do while
   
            // Handle the scenario when the character read is '\n' 
            if(*c == '\n') {
                chars++; // increment the character count
  
                if((*prev>='0' && *prev<='9') || (*prev>='a' && *prev<='z') || (*prev>='A' && *prev<='Z')) {
                    wordsInLine = wordsInLine + 1; // to include the last word in the line
                    tempWord[k] = '\0'; //add '\0' at the end of the word to make it string compatible

                    // Get the 3 longest words in the file
                    if(strlen(tempWord) > longestWordsLen[0]) {
                        longestWordsLen[0] = strlen(tempWord);
                        strcpy(longestWord1, tempWord);
                    }
                    else if(strlen(tempWord) > longestWordsLen[1]) {
                        longestWordsLen[1] = strlen(tempWord);
                        strcpy(longestWord2, tempWord);
                    }
                    else if(strlen(tempWord) > longestWordsLen[2]) {
                        longestWordsLen[2] = strlen(tempWord);
                        strcpy(longestWord2, tempWord);
                    }
      
                    memset(tempWord,'\0',30); //Reset the tempWord array so that next word can be stored
                    k = 0;
                } // end of if 
            }// end of if(*c == '\n') 

            // Get shortest line in terms of words 
            if(shortestLineWords == 0 || wordsInLine < shortestLineWords) {
                shortestLineWords = wordsInLine;
                lineNumWords = j;
            }
      
            j++; //move to the next line
            words = words + wordsInLine; // add the words in each line to get the total number of words in a file

      }// end of while

  printf("\nNumber of Lines : %d", j-1);
  printf("\nNumber of Words : %d", words);
  printf("\nNumber of Characters : %d", chars);
  line[lineNumChars][strlen(line[lineNumChars])-1] = '\0';  //Overwriting the '\n' at the end of line with '\0'
  line[lineNumWords][strlen(line[lineNumWords])-1] = '\0';  //Overwriting the '\n' at the end of line with '\0'
  printf("\nShortest line (%d characters) : %s", shortestLineLen, line[lineNumChars]);
  printf("\nShortest line (%d words) : %s", shortestLineWords, line[lineNumWords]);
  printf("\nLongest word 1: %s", longestWord1);
  printf("\nLongest word 2: %s", longestWord2);
  printf("\nLongest word 3: %s\n\n", longestWord3);
  fclose(in);
  
  for(i = 1; i<j; i++ )
      free(line[i]);

  break; 
  //end of case '4'

  }// end of switch

  return 0;
}
