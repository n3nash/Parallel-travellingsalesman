#ifndef _GLOBAL_H
#define _GLOBAL_H
#include <sys/time.h>

/* Global Variables */
#define NUM_CITIES 48                            // Number of citie
#define pathLen 100					//length of path to read file from
typedef int tour[NUM_CITIES];                         // tour data structure
typedef float distanceMatrix[NUM_CITIES][NUM_CITIES]; // Matrix holding the distance

char *pathName;

void printTour(int *t);
void CheckValidity(int *tour, char* text);
int GetNearestCity(int currCity, unsigned int** dMat, int* visited);
void GenerateTour(int initialCity, int* tourPointer, unsigned int** dMat);
int * GenerateInitPopulation(unsigned int **dMat);
void improveGlobalPopulation(int *, int, int, unsigned int**);
double computeFitness(int * , unsigned int **);
struct timeval globalTime;

//struct stopwatch_t * globalTimer = NULL,

#define OPTPATH "OPTTSPTour.txt"
#define numToursUpdated 2
#define pathString "TSPData.txt"
#define outPathComputed "TSPComputed.dat"
#define outPathActual "TSPActual.dat"
#define numOpenMPthreads_citypaths 10
#define numMPINodes 10
#define numOpenMPThreadsPerMPINode 10
#define numberOfDivisions  4
#define cudaThreadBlocks = 4
#define cudaThreadsPerBlock = 16
#define globalIter 50
#define localIter 50
#define BLOCKSIZE NUM_CITIES //* NUM_CITIES ;  /* threads per block */
#define NUM_BLOCKS 4;   
/******** ERROR CODES *********/

#define INVALID -1

#endif /* _GLOBAL_H */
