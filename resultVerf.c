#include<stdio.h>
#include "global.h"
#include "readFromFile.h"

void printBestPath(int *population, int **dMat , int tourCountOnNode ) {

	int nextIndex = 0 , minDistance = INT_MAX , indexOfBestPath ;

	for(int i=0 ; i < numMPINodes ; i++) {
		for ( int j = 0 ; j < tourCountOnNode[i] ; j++ )
		{
			int distance = computeFitness(population + NUM_CITIES*j);
			if(distance < minDistance)
			  {
				minDistance = distance;
				indexOfBestPath = nextIndex + NUM_CITIES*j;	
		 	  }	
		}
		nextIndex += tourCountOnNode[i]*NUM_CITIES;
		population += nextIndex;
	}

	printf("\nBest Tour\n");
	for( int i = indexOfBestPath ; i < indexOfBestPath + NUM_CITIES ; i++ ) {
		printf(" %d->" , population[i]);
	}
	printf("\nDistance of Best Tour %d " , minDistance);

}

/*
void resultVerification(int *TSPDataComputed, int **TSPData_values)
{

int *correctPath ;
int x_cor , y_cor ;
const char *outfile;
const char *outfile_2;
returnActualPath(path,&correctPath);

//for( int i=0;i<NUM_CITY;i++)
//{
	//calculate fitness and find difference .
	
	strcpy(outfile,outPathActual);
	strcpy(outfile_2,outPathComputed);

	FILE *fp = fopen(outfile,"w");
	FILE *fp_2 = fopen(outfile_2,"w");
	for (i=0; i < NUM_CITY ;i++)
	{
	x_cor = TSPData_values[correctPath[i]][1];
	y_cor = TSPData_values[correctpath[i]][2];
	fprintf (fp, "%d\t%d\n",x_cor , y_cor);
	x_cor = TSPData_values[TSPDataComputed[i]][1];
	y_cor = TSPData_values[TSPDataComputed[i]][2];
	fprintf (fp_2 , "%d\t%d",x_cor,y_cor);
	}

	fflush (fp);
	fflush (fp_2);


	//write into finalOutput.dat the data values.

	
	//plot the 2 different data sets.
}*/
