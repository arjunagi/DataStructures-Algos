#include<stdio.h>

int main() {
char *c[2];
c[0] = "test";
char ch = *(++c[0]);
printf("\n ch: %c\n", ch);
return 0;
}
