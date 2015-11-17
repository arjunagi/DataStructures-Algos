/*
 * Code to detect if a given string has ABA pattern.
 * Ex: Tony's sister helps Tony
 *     A: Tony
 *     B: 's sister helps
 */

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void findPatternIfPresent(char *);

int main() {

    char inp[200];
    printf("\nEnter the input sentence:");
    fgets(inp, 200, stdin);
    findPatternIfPresent(inp);
    return 0;

} // end of main()

/* 
 * Function to detect the ABA pattern.
 * If the pattern is present then print A and B, else print the original string
 */
void findPatternIfPresent(char *inp) {

    char *copy = strdup(inp); // copy the string as strtok manipulates original string 
    char *temp, tempChar;  
    char *word[20]; // to store all the words in the sentence
    char delims[20]; // to store the delimiters
    char *a = (char *) malloc(20); // A
    char *b = (char *) malloc(50); // B
    int i = 1, j=0, numOfWords = 0, numOfDelims = 0;
    int flag = 0; 

    //Get the words from the sentence using the delimiters " ',.\n
    temp = strtok(inp," ',.");

    word[0] = temp; // get the 1st word
    numOfWords++;

    // Get all the words in the sentence
    while(temp != NULL) {
        delims[j] = copy[temp-inp+strlen(temp)]; //store the delimiters in an array
        temp = strtok(NULL," ',.\n");
        word[i] = temp;
        i++;
        numOfDelims++;
        numOfWords++;
        j++;
    }
   
    // A is the first word
    a = word[0];
    i = 0;

    // Compare the first word to all other words in the sentence
    for(j=1;j<numOfWords-1;j++){

        if(strcmp(word[0],word[j]) == 0) {
            if(j == 1) {
            // If the 2nd word is same word as the first, then pattern doesn't exist
                printf("\n No ABA Pattern in the line:%s\n", inp);
                break; 
            }
            else {
            // There is a matching word in the sentence. Set the flag
                flag = 1;
                break;
            }
        }//end of if(strcmp)

        else {
        // Store all other words till a match is found
            if(i<numOfDelims) {
                // add the delimiters to B
                tempChar = delims[i];
                strcat(b,&tempChar);
                i++;
            }
            strcat(b,word[j]);
        }
   }

   if(flag == 1) {
   // If flag is set, then ABA pattern exists. Print A and B.
       printf("\nA:%s\n", a);
       printf("\nB:%s\n", b);
   }
   else {
       printf("\nNo ABA Pattern in the line:%s\n", copy);
   }

} // end of findPatternIfPresent()
