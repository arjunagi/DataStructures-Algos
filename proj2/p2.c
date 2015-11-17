/*
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define NEW(x) (x*)malloc(sizeof(x))

// Data structure for each node of the double-linked list.
typedef struct node { 
  int data;
  struct node * next;
  struct node * prev;
} NODE;

// Data structure for the root node. The root node has the pointers to the head and tail 
// of the list along with the number of nodes in the list.
typedef struct { 
  long len;
  NODE * head;
  NODE * tail;
}ROOT;

// Creat a new node with the data as passed
NODE* makeNode (int data) {
  NODE* temp;
  temp = NEW(NODE);
  if (temp != NULL) { 
    temp->data = data;
    temp->next = NULL;
    temp->prev = NULL;
  }
  return temp;
}

// Create a root node
ROOT* makeRoot () { 
  ROOT * temp;
  temp = NEW(ROOT);
  if (temp != NULL) { 
    temp->len = 0;
    temp->head = NULL;
    temp->tail = NULL;
  }
  return temp;
}

// Create new node with the passed data and insert at the head of the list
int insertAtHead(ROOT *r, int d) { 
  NODE *temp;
  temp = makeNode(d);

  if (temp == NULL) return -1;  // fail, cannot create new NODE

  if (r == NULL) { 
    r = makeRoot();
    if (r == NULL) return -1;   // fail, cannot create ROOT
  }
    
  (r->len)++;

  if (r->len == 1)              // if previously the list is empty
    r->tail = temp;
  else
    r->head->prev = temp;

  temp->next = r->head;
  r->head = temp;

  return 0;
}

// Create new node with the passed data and insert at the tail of the list
int insertAtTail(ROOT *r, int d) { 
  NODE *temp;
  temp = makeNode(d);

  if (temp == NULL) return -1; // fail, cannot create new NODE

  if (r == NULL) { 
    r = makeRoot();
    if (r == NULL) return -1;   // fail, cannot create ROOT
  }

  (r->len)++;

  if (r->len == 1)              // if previously the list is empty
    r->head = r->tail = temp;

  else { 
    r->tail->next = temp;
    temp->prev = r->tail;
    r->tail = temp;
  }
  return 0;
}

// Display the list. Use the pointers in the root node to traverse the list.
void displayList(ROOT *r) { 
  NODE *temp;

  if(r == NULL) printf("\n r is null\n");

  if (r != NULL) { 
    temp = r->head;
    do { 
      printf("%3d ", temp->data);
      temp = temp->next;
    } while (temp != NULL);
  }
  printf("\n");
} 


// Read the number from the file digit by digit and store it in the string. Return the length of the string.
int readNumFromFile(FILE *in, char *num) {
  int c;
  int charCount = 0;
  while((c = fgetc(in)) != EOF) {
      if(strlen(num) == 200)
          num = (char*)realloc(num,200);
      num[charCount++] = (char)c;
  }
  charCount = charCount - 1; //not counting the EOF
  return charCount;
}


// Insert the numbers in the linked list block by block.
void insertBlocksInTheList(int charCount, int blockSize, ROOT* root, char *num) {
  int i=0, j=0;
  int digitsLeft; //Number of digits left to complete the block 
  int data; // data to be stored in each node of linked list
  char tempNum[blockSize]; //temporary array used to cover char to int

  // If the first block will have less digits than block size, then take only the required number of digits.
  // Ex: If number is 12345 and block size is 2, then the first block will just have 1 in it.
  if((digitsLeft = charCount%blockSize) != 0) {
      for(i=0;i<=digitsLeft-1;i++)
          tempNum[i] = num[i];
      data = atoi(tempNum);
      insertAtTail(root, data);
  }

  // insert all other number in the linked list according to block size
  for(;i<=charCount-1;) {
      memset(tempNum,'0',blockSize);
      for(j=0;j<blockSize;j++,i++)
          tempNum[j] = num[i];
      data = atoi(tempNum);
      insertAtTail(root, data);
  }
}

// Add numbers in two linked lists num1 and num2 and return the number of block operations.
// Addition of 2 blocks is 1 block operation. If there is a carry, the it is also counted as 1 block operation.
int addAndReturnBlockOps(int blockSize, NODE* num1, NODE* num2, ROOT* sumRoot) {
  int sum=0, carry=0;
  int toGetBlockSize = (int) pow((double) 10,blockSize);
  int numOfBlockOps = 0;
  while(num1!=NULL || num2!=NULL) {
      sum = carry + ((num1!=NULL)? num1->data: 0) + ((num2!=NULL)? num2->data: 0);
      carry = (sum >= toGetBlockSize)? 1 : 0;
      // update sum if it is greater than 10
      sum = sum % toGetBlockSize;
      insertAtHead(sumRoot, sum);
      if((num1!=NULL && num1->data != 0) && (num2!=NULL && num2->data != 0)) numOfBlockOps++;
      if(carry == 1) numOfBlockOps++;
      if(num1) num1 = num1->prev;
      if(num2) num2 = num2->prev;
  }
  return numOfBlockOps;
}


// Subtract numbers in two linked lists num1 and num2 and return the number of block operations.
// Subtraction of 2 blocks is 1 block operation. If there is a borrow, the it is counted as 2 block operation.
int diffAndReturnBlockOps(int blockSize, NODE* num1, NODE* num2, ROOT* diffRoot) {
  int diff=0, borrow=0;
  int addThisForBorrow = (int) pow((double) 10,blockSize);
  int numOfBlockOps = 0;
  int b1,b2; 
  while(num1!=NULL || num2!=NULL) {
      b1 = (num1!=NULL)? num1->data: 0;
      b2 = (num2!=NULL)? num2->data: 0;
      if(b1>=b2) {
          diff = b1-b2;
          insertAtHead(diffRoot, diff);
          if(b1!=0 && b2!=0) numOfBlockOps++;
      }
      else {
          // b1<b2. Hence we need to borrow from next node
          b1 = b1 + addThisForBorrow;                  // 1 block operation
          num1->prev->data = num1->prev->data - 1;     // 1 block operation
          diff = b1-b2;                                // 1 block operation
          insertAtHead(diffRoot, diff);
          numOfBlockOps = numOfBlockOps + 3;
      }
      if(num1) num1 = num1->prev;
      if(num2) num2 = num2->prev;
  }
  return numOfBlockOps;
}

/*
   argc - number of total arguments, i.e number of argv array elements
   argv - array of arguments
          argv[0] - a.out
          argv[1] - block size
          argv[2] - input file 1
          argv[3] - input file 2
          argv[4] - result file
 */
int main(int argc, char *argv[]) {

  // If the number of arguments is not 5(a.out blockSize inp_file1 inp_file2 result_file), print error and exit
  if(argc != 5) {
    printf("\nWrong number of options provided for a.out\n");
    printf("\nThe usage is: a.out -blockSize inp_file1 inp_file2 result_file\n");
    exit(0);
  }
 
  int blockSize = atoi(&argv[1][1]);   //number of digits to be considered for each operation.
   
  // If the second argument,i.e the block size is not between 0 and 4, print error and exit
  if(!(0<blockSize && blockSize<=4)) {
    printf("\nBlock size %d is not correct. It should be 1,2,3 or 4.\n", blockSize);
    exit(0);
  }

  FILE * in1 = fopen(argv[2], "r"); 
  FILE * in2 = fopen(argv[3], "r");
  FILE * out = fopen(argv[4], "w");
  
  char *num1AsString = (char*) malloc(200); // String to read the number from file 1
  char *num2AsString = (char*) malloc(200); // String to read the number from file 2
  int charCount1, charCount2; // Number of digits in each number
  int i=0;
  int addBlockOps,diffBlockOps,prodBlockOps; // Number of block operations for addition, subtraction and multiplication
  ROOT *root1 = makeRoot();
  ROOT *root2 = makeRoot();
  ROOT *sumRoot = makeRoot();
  ROOT *diffRoot = makeRoot();
  ROOT *prodRoot = makeRoot();


  // Read digits from input file 1 and store in string num1AsString
  charCount1 = readNumFromFile(in1, num1AsString);
  // Insert the numbers in the list block by block
  insertBlocksInTheList(charCount1, blockSize, root1, num1AsString);

  // Read digits from input file 2 and store in string num2AsString
  charCount2 = readNumFromFile(in2, num2AsString);
  // Insert the numbers in the list block by block
  insertBlocksInTheList(charCount2, blockSize, root2, num2AsString);

  printf("\nNumber from file 1: ");
  displayList(root1);
  printf("Number from file 2:");
  displayList(root2);

  NODE *num1 = NULL; 
  NODE *num2 = NULL; 
  // if num1AsString > num2AsString, then assign num1 as num1AsString. Otherwise num1 is num2AsString.
  // This ensures that num1>num2 always. Perform all operations on num1 and num2.
  if(charCount1 > charCount2) {
      num1 = root1->tail;
      num2 = root2->tail;
  }
  else if(charCount1 < charCount2) {
      num1 = root2->tail;
      num2 = root1->tail;
  }
  else if(charCount1 == charCount2) {
      while(i<charCount1) {
          if(num1AsString[i]>num2AsString[i]) {
              num1 = root1->tail;
              num2 = root2->tail;
              break;
          }
          else if(num2AsString[i]>num1AsString[i]) {
              num1 = root2->tail;
              num2 = root1->tail;
              break;
          }
          if(i==(charCount1-1)) {
              num1 = root1->tail;
              num2 = root2->tail;
              break;
          }
          i=i+1;
      }
  }

  // Add the two number and print the sum and number of block operations  
  addBlockOps = addAndReturnBlockOps(blockSize, num1, num2, sumRoot);
  printf("\nSum of the two numbers: ");
  displayList(sumRoot);
  printf("Number of block ops for addition: %d\n", addBlockOps); 

  // Subtract the two number and print the difference and number of block operations  
  diffBlockOps = diffAndReturnBlockOps(blockSize, num1, num2, diffRoot);
  printf("\nDifference of the two numbers: ");
  displayList(diffRoot);
  printf("Number of block ops for difference: %d\n", diffBlockOps); 

  free(num1AsString);
  free(num2AsString);
}

