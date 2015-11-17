/*
 * Program to print the number of days between 2 given dates of the same year
 * Ex: date 1: 9 10 - Sept 10
 *     date 2: 10 4 - Oct 4
 *     difference between the dates = 24 days
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct dateAndMonth {
    int date;
    int month;
};

int main() {
   
   struct dateAndMonth d1;
   struct dateAndMonth d2;
   int highMonth, highDate, lowMonth, lowDate; //biggest month and date numbers
   int days1, days2, daysInBetween = 0; //number of days in lower numbered months, higher numbered months and the months in between 
   int diff, i=0;
   int totalDays[12] = {31,28,31,30,31,30,31,31,30,31,30,31}; // number of days in 12 months
   printf("\nEnter two dates from a same year(m d m d):");
   scanf("%d %d %d %d", &d1.month, &d1.date, &d2.month, &d2.date);

   // if month is same, just subtract the dates.
   if(d1.month == d2.month) {
       if(d1.date > d2.date)
           diff = d1.date - d2.date;
       if(d2.date > d1.date)
           diff = d2.date - d1.date;
   }

   else {
       // find the earlier month 
       if(d1.month > d2.month) {
           highMonth = d1.month;
           highDate = d1.date;
           lowMonth = d2.month;
           lowDate = d2.date;
       }
       else {
           highMonth = d2.month;
           highDate = d2.date;
           lowMonth = d1.month;
           lowDate = d1.date;
       }

       // For the earlier month, subtract the date from the total number of days to get the remaining days left in that month
       // Ex: Sept 10 - means there are 20 days left in the month
       days1 = totalDays[lowMonth-1] - lowDate;

       // For the later month just the date will give the number of days from the start of month
       days2 = highDate; 

       //if the months are not subsequent, then add the days for the months in between  
       if((highMonth - lowMonth) != 1) {
           for(i=(lowMonth-1); i<(highMonth-2); i++) {
               daysInBetween = daysInBetween + totalDays[i+1];
           }
       }
       // difference between the 2 dates in days left in earlier month + days in between (if any) + days elapsed in later month
       diff = days1 + daysInBetween + days2;
   }

   printf("\nThe difference between the two dates %d %d and %d %d is: %d\n", d1.month, d1.date, d2.month, d2.date, diff);
   
      
   return 0;
}
