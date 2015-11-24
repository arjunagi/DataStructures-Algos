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
  int len;
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

// Write the list pointed by the root r into the file "out"
void writeToFile(FILE* out, ROOT* r, int blockSize) {
  NODE* temp;
  int len = 0, i = 0;
  char zeroArray[blockSize-1];
  
  if(r == NULL) {
      printf("\n Cant write as the result list is empty\n");
      exit(0);
  }

  if (r != NULL) {
    temp = r->head;
    do {
      len = floor(log10(abs(temp->data))) + 1;
      if(len<blockSize) {
          //prepend 0 if the number of digits is less than block size
          for(i=0; i<(blockSize-len); i++)
             zeroArray[i] = '0';
          zeroArray[i] = '\0';
          fprintf(out,"%s",zeroArray);
      }
      fprintf(out,"%d", temp->data);
      temp = temp->next;
    } while (temp != NULL);
  }
}

// Insert the numbers in the linked list block by block.
void insertBlocksInTheList(int charCount, int blockSize, ROOT* root, char *num) {
  int i=0, j=0;
  int digitsLeft; //Number of digits left to complete the block 
  int data=0; // data to be stored in each node of linked list
  char *tempNum = NULL; //temporary array used to convert char to int

  // If the first block will have less digits than block size, then take only the required number of digits.
  // Ex: If number is 12345 and block size is 2, then the first block will just have 1 in it.
  if((digitsLeft = charCount%blockSize) != 0) { 
      tempNum = (char*) malloc(blockSize);
      for(i=0;i<=digitsLeft-1;i++)
          tempNum[i] = num[i];
      tempNum[i] = '\0';
      data = atoi(tempNum);
      insertAtTail(root, data);
      free(tempNum);
  }
 

  // insert all other numbers in the linked list according to block size
  for(;i<=charCount-1;) {
      tempNum = (char*) malloc(blockSize);
      for(j=0;j<blockSize;j++,i++)
          tempNum[j] = num[i];
      tempNum[j] = '\0';
      data = atoi(tempNum);
      insertAtTail(root, data);
      free(tempNum);
  }
}

// Add numbers in two linked lists num1 and num2 and return the number of block operations.
// Addition of 2 blocks is 1 block operation. If there is a carry, the it is also counted as 1 block operation.
int addAndReturnBlockOps(int blockSize, NODE* num1, NODE* num2, ROOT* root1, ROOT* root2, ROOT* sumRoot) {
  int sum=0, carry=0;
  int toGetBlockSize = (int) pow((double) 10,blockSize);
  int numOfBlockOps = 0;
  if(num1==NULL && num2==NULL) {
     printf("\n Both the lists are NULL!\n");
     exit(0);
  }   
  if(num1==NULL) {
      sumRoot->head = root2->head;
      sumRoot->tail = root2->tail;
      return numOfBlockOps;  //This is same as adding all blocks in list2 with 0
  }
  else if(num2==NULL) {
      sumRoot->head = root1->head;
      sumRoot->tail = root1->tail;
      return numOfBlockOps;  //This is same as adding all blocks in list1 with 
  }
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
  int b1,b2; //blocks(nodes of list) 
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

// Multiply numbers in two linked lists num1 and num2 and return the number of block operations.
int prodAndReturnBlockOps(int blockSize, NODE* num1, NODE* num2, ROOT* prodRoot) {
  int numOfBlockOps=0, numOfAddOps=0, flag=0, i=0, tempSum1Flag=0, tempSum2Flag=0;
  int prod; //Prodcut of 2 blocks
  int numOfZero = 0; //number of 0's to be prepended
  int lenOfProd = 1; //Number of digits in the product. Will always be atleast 1 digit.
  int insertInList1=0, insertInList2=0; // flags to indicate which list to include the block in
  char* prodArray = (char*)malloc(blockSize*2); //If 4 is the block size, then the max length of product of 4digit * 4digit is 8.
  char *tempProdArray = NULL, *zeroArray = NULL; //store the product temporarily and the concatenate(prepend) with required number of 0's
  ROOT* list1Root, *list2Root; //The 2 lists we create after multipying the 2 blocks of num2 with all blocks of num1. This list is refreshed for every 2 blocks of num2
  ROOT* tempRoot1, *tempRoot2; //Temporary list to store product of 2 blocks. This is then integrated into list1Root and list2Root
  ROOT* tempSumRoot1, *tempSumRoot2; //To store the sum of the 2 lists(list1Root and list2Root) 
  NODE* tailOfNum1 = num1; //Pointer to the tail of num1.
  NODE* numFromList1, *numFromList2, *numFromTempSum1List, *numFromTempSum2List;


  while(num2!=NULL) {
      list1Root = makeRoot();
      list2Root = makeRoot();
      if(tempSum1Flag==0)tempSumRoot1 = makeRoot();
      if(tempSum2Flag==0)tempSumRoot2 = makeRoot();
      flag = 0; //flag to indicate when the 0 has to be entered in the tail of list2. This will create the 1 node offset required for list2
      insertInList1=1;
      num1 = tailOfNum1; //reset the pointer of num1, so that the next block of num2 can be multiplied with all blocks of num1 from the tail
 
      while(num1!=NULL) {
          prod = (num2->data)*(num1->data); 
          lenOfProd = 1;
          if((num1->data!=0 && num1->data!=1) && (num2->data!=0 && num2->data!=1)) numOfBlockOps++;
          if(prod!=0) lenOfProd = floor(log10(abs (prod))) + 1;
          tempProdArray = (char*) malloc(lenOfProd+1);
          snprintf(tempProdArray,lenOfProd+1,"%d",prod);
          
          //prepend 0's if the product is not of the length blockSize*2
          if(strlen(tempProdArray) < (blockSize*2)) {
              numOfZero = (blockSize*2)-lenOfProd;
              zeroArray = (char*) malloc(numOfZero);
              for(i=0; i<numOfZero; i++)
                   zeroArray[i] = '0';
              zeroArray[i] = '\0';
              prodArray = strcat(zeroArray,tempProdArray);
              prodArray[strlen(prodArray)] = '\0';
          }
          else
             prodArray = tempProdArray;

          tempRoot1 = makeRoot();
          tempRoot2 = makeRoot();

          // Insert the blocks in list1
          if(insertInList1==1) {
              //Store the product in a temporary list
              insertBlocksInTheList(strlen(prodArray),blockSize,tempRoot1,prodArray);
              //Integrate the temporary list into list1
              if(list1Root->len == 0) {
                  list1Root->head = tempRoot1->head;
                  list1Root->tail = tempRoot1->tail;
                  list1Root->len = list1Root->len + tempRoot1->len;
              }
              else {
                  tempRoot1->tail->next = list1Root->head;
                  list1Root->head->prev = tempRoot1->tail;
                  list1Root->head = tempRoot1->head;
                  list1Root->len = list1Root->len + tempRoot1->len;
              }
              if(num1->next == NULL && flag == 0) {
                  // if the block from num1 is the first block, then there should be an offset introduced for list2 which will have
                  // product of block1 of num2 and block2(4,6...) of num1. Hence add 0 as the first node(from tail) in list2
                  insertBlocksInTheList(1, blockSize, tempRoot2, "0");
                  list2Root->head = tempRoot2->head;
                  list2Root->tail = tempRoot2->tail;
                  list2Root->len = list2Root->len + tempRoot2->len;
                  flag = 1;
              }
              
              insertInList1=0;
              insertInList2=1;
              free(tempRoot1);
              free(tempRoot2);
          }
          // Insert the blocks in list2
          else if(insertInList2==1) {
              //Store the product in a temporary list
              insertBlocksInTheList(strlen(prodArray),blockSize,tempRoot2,prodArray);
              //Integrate the temporary list into list2
              if(list2Root->len == 0) {
                  list2Root->head = tempRoot2->head;
                  list2Root->tail = tempRoot2->tail;
                  list2Root->len = list2Root->len + tempRoot2->len;
              }
              else {
                  tempRoot2->tail->next = list2Root->head;
                  list2Root->head->prev = tempRoot2->tail;
                  list2Root->head = tempRoot2->head;
                  list2Root->len = list2Root->len + tempRoot2->len;
              }
              insertInList1=1;
              insertInList2=0;
              free(tempRoot1);
              free(tempRoot2);
          }
          if(num1) num1=num1->prev;
      }
      numFromList1 = list1Root->tail;
      numFromList2 = list2Root->tail;
      
      if(tempSum1Flag == 0) {
          numOfAddOps =  numOfAddOps + addAndReturnBlockOps(blockSize, numFromList1, numFromList2, list1Root, list2Root, tempSumRoot1);
          tempSum1Flag = 1;
          tempSum2Flag = 0;
      }
      else if(tempSum2Flag == 0) {
          numOfAddOps =  numOfAddOps + addAndReturnBlockOps(blockSize, numFromList1, numFromList2, list1Root, list2Root, tempSumRoot2);
          insertBlocksInTheList(1, blockSize, tempSumRoot2, "0");
          tempSum1Flag = 0;
          tempSum2Flag = 1;
      }

      numFromTempSum1List = tempSumRoot1->tail;
      if(tempSumRoot2->head != NULL) numFromTempSum2List = tempSumRoot2->tail;
      else numFromTempSum2List = NULL;
      if(prodRoot!=NULL) {
            free(prodRoot); 
            prodRoot = makeRoot();
      }
      numOfAddOps =  numOfAddOps + addAndReturnBlockOps(blockSize, numFromTempSum1List, numFromTempSum2List, tempSumRoot1, tempSumRoot2, prodRoot);
      free(list1Root);
      free(list2Root);

      if(num2) num2=num2->prev;
  }
  free(prodArray);
  //free(tempProdArray);
  //free(zeroArray);
  free(tempSumRoot1);
  free(tempSumRoot2);
  printf("\nNumber of add operations in multiplication: %d",numOfAddOps);
  printf("\nNumber of multiply operations in multiplication(just the block multiplications): %d",numOfBlockOps);
  numOfBlockOps = numOfBlockOps + numOfAddOps; 
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

  out = fopen(argv[4], "a+");
  // Add the two number and print the sum and number of block operations  
  addBlockOps = addAndReturnBlockOps(blockSize, num1, num2, root1, root2, sumRoot);
  printf("\nSum of the two numbers: ");
  displayList(sumRoot);
  printf("Number of block operations for addition: %d\n", addBlockOps);
  fprintf(out,"sum: %d block operation\n", addBlockOps); 
  writeToFile(out, sumRoot, blockSize);

  // Multiply the two number and print the product and number of block operations
  prodBlockOps = prodAndReturnBlockOps(blockSize, num1, num2, prodRoot);
  printf("\nProduct of the two numbers: ");
  displayList(prodRoot);
  printf("Number of block operations for multiplication: %d\n", prodBlockOps);
  fprintf(out,"\nprod: %d block operation\n", prodBlockOps); 
  writeToFile(out, prodRoot, blockSize);

  // Subtract the two number and print the difference and number of block operations  
  diffBlockOps = diffAndReturnBlockOps(blockSize, num1, num2, diffRoot);
  printf("\nDifference of the two numbers: ");
  displayList(diffRoot);
  printf("Number of block operations for subtraction: %d\n", diffBlockOps);
  fprintf(out,"\ndifference: %d block operation\n", diffBlockOps); 
  writeToFile(out, diffRoot, blockSize);

  free(root1);
  free(root2);
  free(sumRoot);
  free(diffRoot);
  free(prodRoot);
  free(num1AsString);
  free(num2AsString);
  fclose(in1);
  fclose(in2);
  fclose(out);
}

