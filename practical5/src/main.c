// --------------------------------------------------------------------------------------------
// Author: Gahan Saraiya
// GiT: http://github.com/gahan9/
// StackOverflow: https://stackoverflow.com/users/story/7664524
// Website: http://gahan9.github.io/
// --------------------------------------------------------------------------------------------
// Hybrid implementation of Openmp and MPI
// Node x Core
// 1 x 1
// 1 x 4
// 2 x 1
// 2 x 2
// 2 x 4

#include <stdio.h>
#include <string.h>
#include "mpi.h"
#include <stdlib.h>
#include <stddef.h>
#include <math.h>

#define ARRAY_SIZE 4000
#define REPEAT     1
#define NUM_THREADS 2

#define CHUNKSIZE 100

void worker_code(double* vector1, double* vector2, double* result){
	int len;
	char processor_name[200];
	int tid, i, chunk;
	// initialize arraysc
	chunk = CHUNKSIZE;
	int total_threads = NUM_THREADS;
	MPI_Get_processor_name(processor_name, &len);
	#pragma omp parallel shared(vector1, vector2, result, total_threads, chunk) private(i,tid) num_threads(total_threads)
	// #pragma omp parallel shared(vector1, vector2, result, total_threads, chunk) private(i,tid)
	{
		tid = omp_get_thread_num();
		// #pragma omp parallel for num_threads(total_threads)
		#pragma omp for schedule(dynamic, chunk)
		for (i=0; i<ARRAY_SIZE; i++){
			result[i] = vector1[i] + vector2[i];
			printf("[%s:%d]: result[%d] is %f\n", processor_name, tid, i, result[i]);
		}
	}
}

double* generate_array(int no_of_elements) {
	int i;
    // no_of_elements : Generate array of `no_of_elements` number of elements
	double* array = (double*) malloc(no_of_elements*sizeof(double));
	for(i=0; i<no_of_elements; i++)
		array[i] = rand()%10000;
	return array;
}

int main(int argc, char **argv ) {
	// Generate input vectors and destination vector
	double *vector1 = generate_array(ARRAY_SIZE);
	double *vector2 = generate_array(ARRAY_SIZE);
	double *result_vector = (double*) malloc(ARRAY_SIZE*sizeof(double));
	
	char message[20];
	int i, rank, size, type=99;

	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if(rank == 0) {
		strcpy(message, "Valar Morgholis!!");
		for (i=1; i<size; i++)
			MPI_Send(message, 20, MPI_CHAR, i, type, MPI_COMM_WORLD);
	}
	else
		MPI_Recv(message, 20, MPI_CHAR, 0, type, MPI_COMM_WORLD, &status);
	worker_code(vector1, vector2, result_vector);
	//all MPI processes run OpenMP code, no message passing
	printf("Kingslayer-%d send you a message : %s\n", rank, message);
	MPI_Finalize();
	return 0;
}
