#include "mpi.h"
#include <cstdio>
#include <iostream>
#include <random>
#include <math.h>
#include <cmath>
#include <cstdlib>

#define TOTAL_NUMBER 100000

int main (int argc,  char *argv[]) {

   int myid, numprocs;
   int namelen;
   int* numbers = new int[TOTAL_NUMBER];
   char processor_name[MPI_MAX_PROCESSOR_NAME];

   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
   MPI_Comm_rank(MPI_COMM_WORLD, &myid);
   MPI_Get_processor_name(processor_name, &namelen);
 
   printf("Process %d on %s\n", myid, processor_name);
 
   srand(time(NULL)+myid);

   int i;
   int part_sum = 0;
   
   // master and slaves will do the same work
   double x=0, y=0;
   int part_total = 0;
   for (i=0; i<TOTAL_NUMBER; i++) {
      x = ((double)rand() / (double)RAND_MAX);
	y = ((double)rand() / (double)RAND_MAX);
      	 
	if( sqrt( x*x + y*y) <= 1)
      part_total++; //counts what is inside the circle
   }
      
   std::cout << "Process: " << myid << " - Points within box: " << part_total  << std::endl;
   part_sum += part_total;
   

   int sum = 0;
   MPI_Reduce(&part_sum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

   if (myid == 0) {
	std::cout << "Total sum: " << sum << std::endl;
	std::cout << "Ratio: " <<(double) sum / (double)(TOTAL_NUMBER*numprocs) << std::endl;
	std::cout << "PI: " << 4.0 *(double) sum / (double)(TOTAL_NUMBER*numprocs) << std::endl;  
   }

   MPI_Finalize();
}
