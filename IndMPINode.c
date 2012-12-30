#include <omp.h>
#include "globalData.h"
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <stdlib.h>

void ProcessRoute(int*,int,const int*);
void TSPSwapRun(int *,const int *);

struct indexesSend{
long max;
int cityIndex;
};

void ProcessRoute(int* localPopulation, int numberOfTours,const int* coords)
{
  int tour = 0 , city , prevX = 0 , prevY = 0 , i = 0 , j , populationStartIndex ;
  long distance = 0;
  struct indexesSend firstTourIndex , secondTourIndex;
  firstTourIndex.max = INT_MAX , secondTourIndex.max = INT_MAX ;
  int numCities = NUM_CITIES;
  omp_set_num_threads(numberOfTours);
  long distanceArray[numberOfTours];
  int tempTours[NUM_CITIES];

//  printf ("\n\nNumber of Tours %d " , numberOfTours);
 
  for(i = 0 ; i < numberOfTours; i++)
  {
    distanceArray[i] = 0;
  }
  
  #pragma omp parallel default(shared) shared(localPopulation, numCities, numberOfTours ,coords,  distanceArray) private(tour,prevX , prevY ,  distance , i )
  {
    #pragma omp for
    for(tour = 0; tour < numberOfTours; tour++)
    {
   //   if ( tour == 1 )
//		j = 0;
      distance = 0;
//     printf("\nfirst element is %d and tour %d" , (localPopulation + (NUM_CITIES*tour))[0] , tour);
      TSPSwapRun((int *)(localPopulation + (NUM_CITIES * tour)) , (const int*)coords);

	#pragma omp barrier

      prevX = (coords + (2 * ((localPopulation + (numCities*tour))[0] - 1)))[0]; 
      prevY = (coords + (2 * ((localPopulation + (numCities*tour))[0] - 1)))[1];
//	printf ("\nAfter Cuda Kernel " );   
 
      for(int i = 1; i < numCities; i++)
      {
        city = (localPopulation + (numCities*tour))[i] - 1;
        distance += ((((coords + (city)*2))[1] - prevY) * ((coords + (city*2))[1] - prevY)) + (((coords + (city*2))[0] - prevX) * ((coords + (city*2))[0] - prevX));
        prevX = *(coords + (city*2));
        prevY = *(coords + (city*2)+1);

      }
      prevX = (coords + (2 * ((localPopulation + (numCities*tour))[0] - 1)))[0];
      prevY = (coords + (2 * ((localPopulation + (numCities*tour))[0] - 1)))[1];

      distance += ((((coords + (city)*2))[1] - prevY) * ((coords + (city*2))[1] - prevY)) + (((coords + (city*2))[0] - prevX) * ((coords + (city*2))[0] - prevX));

      distanceArray[tour] = distance;
    }
  }


  for ( i = 0 ; i < numberOfTours ; i ++ )
  {
    if( distanceArray[i] < firstTourIndex.max ) {
    secondTourIndex.max = firstTourIndex.max;
    secondTourIndex.cityIndex = firstTourIndex.cityIndex;
    firstTourIndex.max = distanceArray[i];
    firstTourIndex.cityIndex = i;}
    
    else if (distanceArray[i] < secondTourIndex.max){
      secondTourIndex.max = distanceArray[i];
      secondTourIndex.cityIndex = i;}
  }

  populationStartIndex = 0;
  for ( i = 0 ; i < numCities ; i++ )
  {
 
    tempTours[i] = (localPopulation + (numCities*firstTourIndex.cityIndex))[i];
    (localPopulation + (numCities*(populationStartIndex + 1)))[i] = (localPopulation + (numCities*secondTourIndex.cityIndex))[i];
  }
  for ( i = 0 ; i < numCities ; i++)
  {
    (localPopulation + (numCities*populationStartIndex))[i] = tempTours[i];
  }
}

/*
int main()
{
  int i ,j;
  int tour[15*NUM_CITIES];// = {0, 2, 1 ,3, 4, 6,5, 7, 8, 10, 9, 11, 12, 14, 13, 15 , 16};
  int* coords = (int *)malloc(2 * NUM_CITIES * sizeof(int *));

 for ( j = 0; j < 15 ; j ++ )
 {
  for(i = 0; i < NUM_CITIES; i++)
  {
    tour[j*NUM_CITIES + i] = i + 1;
//    tour[1*NUM_CITIES+i] = i + 1;
  //  tour[2*NUM_CITIES+i] = i + 1;
  //   tour[3*NUM_CITIES+i] = i + 1;
  //   tour[4*NUM_CITIES+i] = i + 1;
   
   }
}
  for(i = 0; i < NUM_CITIES; i++)
  {
    coords[2 * i]= i;
    coords[(2 * i) + 1] = i;
  }
  ProcessRoute((int *)tour , 15 , (const int *)coords);
  for(i = 0; i < NUM_CITIES; i++)
    printf("%d ", tour[i]);
  printf("\n");
}
*/



