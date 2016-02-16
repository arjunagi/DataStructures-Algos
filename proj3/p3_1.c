#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define NUM_OF_LINES 6
#define NEW(x) (x*)malloc(sizeof(x))

//Data structure for each station.
typedef struct station {
  char* line; //the line on which this station is located
  char* name;
  bool isTransferPossible; //boolean to indicate if transfer is possible to other lines
  int numOfTransferLines; //number of other lines a transfer can be done to
  int timeToReach; //Time to reach this station from the first station on this line.
  int stopTime; //Duration for which the train stops on this station.
  char* transferLines[3];
  bool visited;
  struct node * next;
  struct node * prev;
} STATION;

// Data structure for the root node. The root node has the pointers to the first and last stations and also the number of stations on a line.
typedef struct {
  int numOfStations;
  STATION * start;
  STATION * end;
}ROOT;

/*
 *****************************************************************************************************************
 * Stores the pointers to the transfer lines for a transfer station. For example, for Fort Totten, it will store 
 * pointers to Fort Totten in the green, red and yellow lines. This way if we have to transfer from green to red,
 * we can get the "Fort Totten" node on red line linked list.
 *****************************************************************************************************************
 */
typedef struct transferStations {
  STATION* transferLines[4]; // Accoding to the map, there are max 4 lines at a station (L'Enfant Plaza station)
} TRANSFERSTATION;


// Creat a new node with the data as passed
STATION* makeNode(char* line, char* name, bool isTransferPossible, int numOfTransferLines, int timeToReach, int stopTime, char* transferLines[], bool visited) {
  STATION* temp;
  temp = NEW(STATION);
  if (temp != NULL) {
    temp->line = line;
    temp->name = name;
    temp->isTransferPossible = isTransferPossible;
    temp->numOfTransferLines = numOfTransferLines;
    temp->timeToReach = timeToReach;
    temp->stopTime = stopTime;
    for(int i=0; i<numOfTransferLines; i++)
        temp->transferLines[i] = transferLines[i];
    temp->visited = visited;
    temp->next = NULL;
    temp->prev = NULL;
  }
  return temp;
}

// Create new node with the passed data and insert at the tail of the list
int insertAtTail(ROOT *r, char* line, char* name,int numOfTransferLines, int timeToReach, int stopTime, char* transferLines[]) {
  NODE *temp;
  if(numOfTransferLines!=0) isTransferPossible = true;
  temp = makeNode(line,name,isTransferPossible,numOfTransferLines,timeToReach,stopTime,transferLines);

  if (temp == NULL) return -1; // fail, cannot create new NODE

  /*if (r == NULL) {
    r = makeRoot();
    if (r == NULL) return -1;   // fail, cannot create ROOT
  }*/

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

// Create a root node
ROOT* makeRoot(int numberOfStations) {
  ROOT * temp;
  temp = NEW(ROOT);
  if (temp != NULL) {
    temp->numOfStations = numberOfStations;
    temp->start = NULL;
    temp->end = NULL;
  }
  return temp;
}


void readStationsFromFile() {

  FILE *metro = fopen("metro.txt", "r");
  if(metro == NULL) {
    printf("\nmetro.txt file could not be opened\n");
    exit(0);
  }

  int ch=0;
  char* lineInfo = NULL;
  char* lineName = NULL;
  int numOfStations = 0;
  char* stationInfo = NULL;
  char* stationName = NULL;
  int numOfTransfers = 0;
  int stopTime = 0;
  int timeToReach = 0;
  ROOT* root[6] = NULL;

  for(int i=0; i<NUM_OF_LINES; i++) {
    lineInfo = malloc(20);
    lineName = malloc(10);
    fgets(lineInfo,20,metro);
    sscanf(lineInfo, "%s (%d)", lineName, &numOfStations);
    makeRoot(numOfStations);
    printf("\nLine name: %s\nnumber of stations: %d\n", lineName, numOfStations);

    for(int j=0;j<numOfStations;j++) {
      stationInfo = malloc(100);
      stationName = malloc(20);
      fgets(stationInfo,100,metro);
      sscanf(stationInfo,"%s %d %d %d", stationName, &numOfTransfers, &timeToReach, &stopTime);
      insertAtTail(lineName,stationName,numOfTransferLines,timeToReach, stopTime, char* transferLines[])
      //printf("Name: %s  Transfers: %d  Stop: %d\n", stationName, numOfTransfers, stopTime);
    }
   char *blank_line = calloc(3, sizeof(char));
   fgets(blank_line, 3, metro); 
  }
   

}


int main() {
   readStationsFromFile();
return 0;
}
