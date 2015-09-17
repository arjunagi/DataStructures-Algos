/*
  Print the calendar of Sept. 2015 in the same format as
  the output of command "cal 9 2015".
 */

#include <stdio.h>
#include <string.h>

int main(void) {

  char *days[7] = {"S","M","Tu","W","Th","F","S"};
  int date = 2; //staring from 2nd
  char dateAsString[3]; //convert date to String format
  int lenOfDate; // length of date in string format
  char cal[160]; // calendar to be printed
  int row=0,col=0,i=0;
  int row1 = 0; //0 if row 1 was not added. 1 if row 1 was added.

  strcpy(cal,"   September 2015   \n"); //First line of calendar

  // There are 6 rows and 20(including spaces) columns in Sept 2015 calendar
  for(row=0;row<6;row++) {
    if(row == 0 ) {
      do {
        if(strlen(days[i])==1){  //For S,M,W,F,S, add a space before the letters
          strcat(cal," ");
          strcat(cal,days[i]);
        }
        else
          strcat(cal,days[i]);  //Tu and Th

        strcat(cal," "); //add a space after each day
        i=i+1;
      }while(i<7);
    }
    else {
      col = 0; //counter to count to column. There are 20 columns in the calendar, including spaces.
      strcat(cal,"\n"); //add a new line after 20 columns
      do {
        if(row==1 && row1==0) {
          strcat(cal,"       1 "); //add row 1 starting from 1st. Add spaces before '1' as 1st is on Tu
          col=col+9;
          row1 = 1;                //indicates that row 1 has been added.
        }
        lenOfDate = sprintf(dateAsString,"%d",date);
        if(lenOfDate==1) { //if date is single digit, add a space before it
          strcat(cal," ");
          strcat(cal,dateAsString);
          strcat(cal," ");
          col=col+3;
        }
        else {
          strcat(cal,dateAsString);
          strcat(cal," ");
          col+=3;
        }
        date+=1;
      }while(col<20 && date<31);
    }
  }

  printf("\n%s\n",cal);
  return 0;
}

