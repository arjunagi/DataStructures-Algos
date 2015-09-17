/*
 * Program to take 3 integer inputs from the user
 * and print them in increasing order
 *
 * Author: Karthik Arjunagi
 */

#include <stdio.h>

int main(void) {

  int a,b,c;
  int big,small,smallest;
  printf("\nEnter 3 numbers:");
  scanf("%d %d %d",&a,&b,&c);    //Take 3 inputs

  if(a>b && a>c) {
    big=a;
    if(b>c) {
      small=b;
      smallest=c;
    }
    else {
      small=c;
      smallest=b;
    }
  }
  else if(b>a && b>c) {
    big=b;
    if(a>c) {
      small=a;
      smallest=c;
    }
    else {
      small=c;
      smallest=a;
    }
  }
  else {
    big=c;
    if(a>b) {
      small=a;
      smallest=b;
    }
    else {
      small=b;
      smallest=a;
    }
  }

  printf("\n%d %d %d\n",smallest,small,big);
  return 0;
}

