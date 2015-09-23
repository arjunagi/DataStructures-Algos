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

  char ch[500];
  char ch1[500];
  char ch2[500];
  char *line1=NULL, *line2=NULL;
  int i=0;
  size_t lineSize = 0;
  ssize_t read;
  char userInp='p';
  char grepWord[11], oneWord[500];
  int grepWordLen = 0, lineNum = 1;
  int c,lines=0,words=0,chars=0,lineLenWord=0,lineLenChars=0; 
  char prev;
  char *shortestLineChars, *shortestLineWords; //shortest line in terms of characters and words
  char *longestWords[3]; //longest words
  int sLine=0, sWord=0; //shortest line length in terms of characs and shortest line in terms of words
  int lw1=0,lw2=0,lw3=0; //top 3 longest words lengths

  switch (argv[1][0]) {
  
   //Copying files
   case'0':
     while(fgets(ch,100,in) != NULL)
       fprintf(out,"%s", ch);
     fclose(out);
     fclose(in);
     break;

   //Interleave
   case'1':
     while(((line1=fgets(ch1,500,in1)) != NULL) || ((line2=fgets(ch2,500,in2)) != NULL))
     {
        if(line1!=NULL) {
          printf("\nch1:%s\n",ch1);
          fprintf(out,"%s", ch1);} 
        if(line2!=NULL){
          printf("\nch2:%s\n",ch2);
          fprintf(out,"%s", ch2);}
     }
     fclose(in1);
     fclose(in2);
     fclose(out);
     break;
     
   //more
   //Print first 10 lines from a file and wait for user input
   //if userInp is 'p', print next 10 lines
   //if userInp is 'n', print next line
   //if userInp is 'q', quit
   case '2':
     do {
       if(userInp=='p') {
         //Read 10 lines from file and print it
         for(i=0;i<10;i++) {
           read = getline(&line1, &lineSize, in);
           if(read != -1)
             printf("%s",line1);
           else
             exit(0);
         }
       }
       else if(userInp=='n') {
       // Read the next line and print it
         read = getline(&line1, &lineSize, in);
         if(read != -1)
           printf("%s", line1);
         else
           exit(0);
       }
       scanf("%c",&userInp);
     } while((userInp!='q') || (userInp=='n') || (userInp=='p'));
     break;

  //grep - case sensitive
  case '3':
    printf("\nInput search string (10 char max): ");
    fgets (grepWord, 11, stdin); //get the search string. Length is 11 as fgets read \n also.
    grepWordLen = strlen(grepWord);
    if ((grepWordLen>0) && (grepWord[grepWordLen - 1] == '\n'))
        grepWord[grepWordLen - 1] = '\0';
    if(grepWordLen <= 10) {
      while((fgets(oneWord,500,in)) != NULL) {
        if((strstr(oneWord,grepWord)) != NULL ) {
          printf("\nline %d: %s",lineNum,oneWord);
        }
        lineNum+=1;
      }
    }
    else {
      printf("\n Search string should be 10 characters max");
      exit(0);
    }
    break;
  
    // Word count 
    case '4':
    while(!feof(in))
    {
      prev = c;  //Store the previous character
      c = fgetc(in); //Get the current character
      chars++; //increment the number of character
      //If character is new line, incremenet the number of lines parameter
      if(c == '\n')
      {
        if((lineLenChars < sLine) || (sLine==0))
          sLine = lineLenChars;
        lineLenChars = 0; //Reset the parameter to count the number of characters in a line
        lines++;
        //If current character is \n and the previous character was an alphabet or a number, increment the number of words to include the last word of the previous line
        if((prev>='0' && prev<='9') || (prev>='a' && prev<='z') || (prev>='A' && prev<='Z'))
          words++;
      }
      else {
        lineLenChars++; //increment the number of chars in a line
        if((c>='0' && c<='9') || (c>='a' && c<='z') || (c>='A' && c<='Z'))
        {
          if((lineLenWord < sWord) || (sWord==0)) {
            sWord = lineLenWord; printf("\nsWord: %d", sWord);}
          lineLenWord = 0; //reset to 0
          //lineLenWord++; //increment the number of words in a line.
        }
        else {
          //if((lineLenWord < sWord) || (sWord==0))
            //sWord = lineLenWord;
          lineLenWord++; //increment the number of words in a line.
          //lineLenWord = 0; //reset to 0
          //increment number of words if current is not alphabet or number, but the prev character was.
          if((prev>='0' && prev<='9') || (prev>='a' && prev<='z') || (prev>='A' && prev<='Z')) {
            words++;
          }
        }
      }
    }
    printf("\n Number of lines: %d", lines);
    printf("\n Number of words: %d", words);
    printf("\n Number of characters: %d", chars);
    printf("\n Shortest Line in terms of characs: %d", sLine);
    printf("\n Shortest Line in terms of words: %d", sWord);
    break;
  }

  return 0;
}
