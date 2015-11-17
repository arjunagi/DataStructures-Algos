#include <stdlib.h>
#include <stdio.h>

#define NEW(x) (x*)malloc(sizeof(x))

typedef struct node {
    int * date[2];    //date[0] for month and date[1] for day
    struct node * next; 
    struct node * prev; 
}NODE;
 
typedef struct {
    struct node * first; 
    struct node * last; 
}SCHEDULE;

NODE * makeNode (int month, int day)
{ 
    NODE * temp;
    temp = NEW(NODE);
    if (temp != NULL)
    { 
        temp->date[0] = &month;
        temp->date[1] = &day;
        temp->next = NULL;
        temp->prev = NULL;
    }
    else {
        printf("\nno memory allocated\n");
        exit(0);
    }
    return temp;
}

SCHEDULE * makeSchedule (void)
{ 
    SCHEDULE * temp;
    temp = NEW(SCHEDULE);
    if (temp != NULL)
    { 
        //temp->num = 0;
        temp->first = NULL;
        temp->last = NULL;
    }
    return temp;
}

int insertAtPosition(SCHEDULE *s, int month, int day)
{
  NODE * temp, *this;
  temp = makeNode(month,day);

  if (temp == NULL) return -1;  // fail, cannot create new NODE

  if (s == NULL)
  { 
    s = makeSchedule();
    if (s == NULL) return -1;   // fail, cannot create ROOT
  }

  this = s->first;
  if ((this->date[0]) <= (temp->date[0])) {// insert at head
      temp->next = s->first;
      s->first = temp;
  }

  else
  { 
      while (this->next != NULL && ((this->next->date[0]) > (temp->date[0])))
      {
          NODE *temp1 = temp;
          temp1->next->prev = temp;
          temp->next = temp1->next;
          temp->prev = temp1;
          temp1->next =temp;
          //this = this->next;
      }

    if (this->next == NULL)     // update tail if insert at tail
    { s->last = temp;
      this->next = temp;
      //(r->num)++;
    }
    else
    { temp->next = this->next;
      this->next = temp;
      //(r->num)++;
    }
  }
  return 0;
}

void display(SCHEDULE *s){
 NODE *tmp = s->first;
 do{
   printf("%d/%d ",tmp->date[0],tmp->date[1]);
   if(tmp->next != s->first){
     printf(" --> ");
   }
   tmp = tmp->next;
 }while(tmp != NULL && tmp != s->first);
}

int main() {
   
  SCHEDULE *s = NEW(SCHEDULE); 
  FILE *f = NULL;
  int month,day;
  int search_month = 1,search_day = 2;

  /*if((search_month = atoi(argv[2])) ==0 || (search_day = atoi(argv[3])) ==0){
    printf("values provided for month and day are not valid\n");
    exit(-1);
  }*/

  s->first = NULL;
  s->last = NULL;

  f = fopen("test.txt","r");
  if(f == NULL){
    printf("invalid file \n");
    exit(0);
  }
  
  int i =0;
  while(fscanf(f,"%d/%d",&month,&day)!=-1){
    int m  = month;
    int d = day;
    insertAtPosition(s,m,d);
    if(i ==3){
      break;
    }
    i = i+1;
  }

  display(s);
  printf("\n");
  printf("\n");
  search(s,search_month,search_day);
  
return 0;
}
