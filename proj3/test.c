#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define NUM_OF_LINES 6
#define NEW(x) (x*)malloc(sizeof(x))

// Global variables to store the source and destination stations 
char* sourceName = NULL;
char* destinationName = NULL;

//Data structure for each station.
typedef struct station {
  char* lineName; //the line on which this station is located
  char* stationName;
  bool isTransferPossible; //boolean to indicate if transfer is possible to other lines
  int numOfTransferLines; //number of other lines a transfer can be done to
  int timeToReach; //Time to reach this station from the first station on this line.
  int stopTime; //Duration for which the train stops on this station.
  char* transferLines[4];
  int transferTimes[4];
  bool visited;
  struct station* next;
  struct station* prev;
} STATION;

//STATION *source;
//STATION *destination;

// Data structure for the line(root) node. The root node has the pointers to the first and last stations and also the number of stations on a line.
typedef struct {
  int numOfStations;
  STATION * start;
  STATION * end;
}LINE;

/*
 ********************************************************************************
 * Structure to store a transfer station and its properties:
 * 1.Pointer to the transfer station node in the line linked list.
 * 2.Name of the station
 * 3.The current line color. 
 ********************************************************************************
 */
typedef struct transferStations {
  STATION* station; // Pointer to the transfer station in a line  
  char* stationName;
  char* lineName;
} TRANSFERSTATION;


// Create a line (Root)
LINE* makeLine() {
  LINE * temp;
  temp = NEW(LINE);
  if (temp != NULL) {
    temp->numOfStations = 0;
    temp->start = NULL;
    temp->end = NULL;
  }
  return temp;
}


// Creat a new node with the data as passed
STATION* makeStation(char* lineName, char* stationName, bool isTransferPossible, int numOfTransferLines, int timeToReach, int stopTime, bool visited, char* transferLines[], int transferTimes[]) {
  STATION* temp;
  temp = NEW(STATION);
  if (temp != NULL) {
    temp->lineName = lineName;
    temp->stationName = stationName;
    temp->isTransferPossible = isTransferPossible;
    temp->numOfTransferLines = numOfTransferLines;
    temp->timeToReach = timeToReach;
    temp->stopTime = stopTime;
    temp->visited = visited;
    temp->next = NULL;
    temp->prev = NULL;
    if(numOfTransferLines!=0) {
      for(int i=0; i<numOfTransferLines; i++) {
        temp->transferLines[i] = transferLines[i];
        temp->transferTimes[i] = transferTimes[i];
      }
    }
  }
  return temp;
}

TRANSFERSTATION* makeTransferStation(STATION *station, char* stationName, char* lineName) {
  TRANSFERSTATION *temp;
  temp = NEW(TRANSFERSTATION);
  if(temp!=NULL) {
    temp->station = station;
    temp->stationName = stationName;
    temp->lineName = lineName;
  }
  return temp;
}

// Create new node with the passed data and insert at the tail of the list
STATION* insertStationInLine(LINE *line, char* lineName, char* stationName, int numOfTransferLines, int timeToReach, int stopTime, char* transferLines[], int transferTimes[]) {
  STATION *temp;
  bool isTransferPossible = false;
  bool visited = false;
  if(numOfTransferLines!=0) isTransferPossible = true;
  temp = makeStation(lineName,stationName,isTransferPossible,numOfTransferLines,timeToReach,stopTime,visited,transferLines,transferTimes);
  
  if (temp == NULL) return NULL; // fail, cannot create new NODE

  if (line == NULL) {
    line = makeLine();
    if (line == NULL) return NULL;   // fail, cannot create ROOT
  }

  (line->numOfStations)++;

  if (line->numOfStations == 1)              // if previously the list is empty
    line->start = line->end = temp;

  else {
    line->end->next = temp;
    temp->prev = line->end;
    line->end = temp;
  }
  return temp;
}


void readStationsFromFile(LINE* line[], TRANSFERSTATION* transferStations[], STATION *source, STATION *destination) {

  FILE *metro = fopen("metro.txt", "r");
  if(metro == NULL) {
    printf("\nmetro.txt file could not be opened\n");
    exit(0);
  }

  int ch=0;
  char* lineInfo = malloc(20);
  char* lineName = malloc(10);
  char *blankLine = calloc(5, sizeof(char*));
  int numOfStations = 0;
  char* stationInfo = NULL;
  char* stationName = NULL;
  bool isTransferPossible;
  int numOfTransferLines = 0;
  int stopTime = 0;
  int timeToReach = 0;
  char** transferLines = NULL;
  int transferTimes[4];
  STATION *station = NULL;
  int k=0, n=0, x=0, y=0;
  char *tempTransferLines[8];
  char *temp = NULL;
  bool sourceFound=false, destFound=false;

  for(int i=0; i<NUM_OF_LINES; i++) {
    printf("\nLine: %d\n", i);
    memset(transferTimes, 0, sizeof(transferTimes));
    fgets(lineInfo,20,metro);
    sscanf(lineInfo, "%s (%d)", lineName, &numOfStations);
    line[i] = makeLine();
    printf("\nLine name: %s\nnumber of stations: %d\n", lineName, numOfStations);

    for(int j=0;j<numOfStations;j++) {
      transferLines = malloc(sizeof(char) * 4);
      stationInfo = malloc(100);
      stationName = malloc(30);
      isTransferPossible = false;
      fgets(stationInfo,100,metro);
      sscanf(stationInfo,"%s %d %d %d", stationName, &numOfTransferLines, &timeToReach, &stopTime);
      temp = strtok (stationInfo," ");
      n=0;
      if(numOfTransferLines != 0) {
         isTransferPossible = true;
         while (temp != NULL && n<(4+(numOfTransferLines*2)))  
  	 {
         //At transfer stations, there are 4 strings of station name, transfers, time from first stop, stop time. If there is 1 transfer, then there is 2 
         //more strings - transfer line and transfer time. If there is 2 transfers, then there are 4 more strings and so on.
           if(n>=4)
             tempTransferLines[n-4] = temp;
           temp = strtok(NULL, " ");
           n++;
         }
        x=0, y=0;
        // Store the transfer lines and the transfer times in their respective arrays.
        for(n=0;n<(numOfTransferLines*2);n++) {
          if(n%2 == 0) { transferLines[x] = tempTransferLines[n]; x++; } 
          else { transferTimes[y] = atoi(tempTransferLines[n]); y++; }
        }
      }
      station = insertStationInLine(line[i], lineName, stationName, numOfTransferLines, timeToReach, stopTime, transferLines, transferTimes);
      if(numOfTransferLines != 0) {
         transferStations[k++] = makeTransferStation(station, stationName, lineName);
      }

      // Check if source and destination stations created are correct. If yes, then store their Station objects.
      if((strcmp(stationName,sourceName) == 0) && sourceFound == false) {
         sourceFound = true;
         source = station;
         //source = makeStation(lineName, stationName, isTransferPossible,numOfTransferLines,timeToReach,stopTime,false,transferLines,transferTimes);
         printf("\n\nsource->lineName : %s\n\n", source->lineName);
         //source->lineName = station->lineName;
      }
      if((strcmp(stationName,destinationName) == 0) && destFound == false) {
         destFound = true;
         //destination = makeStation(lineName, stationName, isTransferPossible,numOfTransferLines,timeToReach,stopTime,false,transferLines,transferTimes);
         destination = station;
      }
      printf("Name: %s  Transfers: %d  Stop: %d\n", stationName, numOfTransferLines, stopTime);
   }
   fgets(blankLine, 5, metro); 
   free(transferLines);
   free(stationInfo);
   free(stationName);
  }
  free(lineInfo);
  free(lineName);
  free(blankLine);
  fclose(metro);
}

void displayLine(LINE* line) {
  STATION *temp;
  if(line == NULL) printf("\n line is null\n");

  if (line != NULL) {
    temp = line->start;
    do {
      printf("%s ", temp->stationName);
      temp = temp->next;
    } while (temp != NULL);
  }
  printf("\n");
}


int main(int argc, char *argv[]) {

   if(argc != 2) {
     printf("\nWrong number of options provided for a.out\n");
     printf("\nThe usage is: a.out output_file\n");
     exit(0);
   }
   
   sourceName = malloc(sizeof(char) * 30);;
   destinationName = malloc(sizeof(char) * 30);;
   printf("\nEnter the source station: ");
   scanf("\%s", sourceName);
   printf("\nEnter the destination station: ");
   scanf("\%s", destinationName);

   //STATION *source = NULL;
   //STATION *destination = NULL;
   STATION *source = malloc(sizeof(STATION));
   STATION *destination = malloc(sizeof(STATION));

   if(strcmp(sourceName, destinationName) == 0) {
     printf("\nSource and destination is same!\n");
     exit(0);
   }
  
   FILE * out = fopen(argv[1], "w");

   LINE* line[6] = {NULL}; //There are 6 lines

   //Array of transfer stations. Example: Fort Totten of green line is considered 1 transfer station and For Totten of red is considered as another.  
   TRANSFERSTATION** transferStations;
   transferStations = malloc(sizeof(TRANSFERSTATION) * 92);
   readStationsFromFile(line, transferStations,source,destination);
   printf("\n source obj name: %s in line: %s\n", source->stationName, source->lineName);
   printf("\n dest obj name: %s in line: %s\n", destination->stationName, destination->lineName);
   //displayLine(line[0]);
   //for(int i=0; i<92; i++)
     //printf("\n%s",transferStations[i]->station->stationName);
   free(transferStations);
   
   fclose(out);
   free(source);
   free(destination);
   return 0;
}
