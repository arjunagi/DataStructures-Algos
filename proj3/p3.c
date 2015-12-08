#include<stdio.h>
#include<stdlib.h>

#define NUM_OF_LINES 6
#define NEW(x) (x*)malloc(sizeof((x))

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

  for(int i=0; i<NUM_OF_LINES; i++) {
    lineInfo = malloc(20);
    lineName = malloc(10);
    fgets(lineInfo,20,metro);
    sscanf(lineInfo, "%s (%d)", lineName, &numOfStations);
    printf("\nLine name: %s\nnumber of stations: %d\n", lineName, numOfStations);

    for(int j=0;j<numOfStations;j++) {
      stationInfo = malloc(100);
      stationName = malloc(20);
      fgets(stationInfo,100,metro);
      sscanf(stationInfo,"%s %d %d", stationName, &numOfTransfers, &stopTime);
      printf("Name: %s  Transfers: %d  Stop: %d\n", stationName, numOfTransfers, stopTime);
    }
   char *blank_line = calloc(3, sizeof(char));
   fgets(blank_line, 3, metro); 
  }
   

}


int main() {
   readStationsFromFile();
return 0;
}
