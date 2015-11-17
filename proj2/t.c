#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {

char* prodArray = malloc(8);
strcpy(prodArray,"345");
char temp[2]; 
int i =0;
printf("\n prod array before: %s\n", prodArray);
memset(temp,'0',2);
memmove(prodArray+2,prodArray,3);
for (i = 0; i < 2; ++i)
    {
        prodArray[i] = temp[i];
    }
printf("\n prod array: %s\n", prodArray);
return 0;
}
