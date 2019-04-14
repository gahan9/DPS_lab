// --------------------------------------------------------------------------------------------
// Author: Gahan Saraiya
// GiT: http://github.com/gahan9/
// StackOverflow: https://stackoverflow.com/users/story/7664524
// Website: http://gahan9.github.io/
// --------------------------------------------------------------------------------------------
// Making code sequential code to parallel using openmp
// Do speedup calculation -- Sequential/parallel
// Show profiling and total execution time
// Standard vector addition (serial, without OMP)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <omp.h>
#include <math.h>

#define ARRAY_SIZE 1000000
#define REPEAT     100
#define NUM_THREADS 4


void vector_add(double* vector1, double* vector2, double* result) {
    int i;
	int size_chunks = ARRAY_SIZE/NUM_THREADS;
    #pragma omp parallel num_threads(NUM_THREADS)
	{
        // #pragma omp parallel for num_threads(NUM_THREADS)
        // #pragma omp parallel for
		// #pragma omp for schedule(static)
		// #pragma omp for schedule(static, 100)
		// #pragma omp for schedule(dynamic)
		// #pragma omp for schedule(dynamic, size_chunks)
		// #pragma omp for schedule(auto)
		// #pragma omp for schedule(guided)
		#pragma omp for schedule(guided, size_chunks)
        for (i=0; i < ARRAY_SIZE; i++){
		// for(int i=size_chunks*omp_get_thread_num(); i < size_chunks*(omp_get_thread_num()+1); i++){
            result[i] = vector1[i] + vector2[i];
        }
    }
}


double* generate_array(int no_of_elements) {
    // no_of_elements : Generate array of `no_of_elements` number of elements
	double* array = (double*) malloc(no_of_elements*sizeof(double));
	for(int i=0; i<no_of_elements; i++)
		array[i] = rand()%10000;
	return array;
}

int verify(double* vector1, double* vector2) {
    // Verifying accuracy of computation
	double *adder = (double*) malloc(ARRAY_SIZE*sizeof(double));
	double *verifier = (double*) malloc(ARRAY_SIZE*sizeof(double));
	vector_add(vector1, vector2, adder);

	for(int i=0; i<ARRAY_SIZE; i++) {
		verifier[i] = vector1[i] + vector2[i];
    }
	for(int i=0; i<ARRAY_SIZE; i++){
		if(verifier[i] != adder[i]){
			return 0;
        }
    }        
	return 1;
}


int main() {
	// Generate input vectors and destination vector
	double *vector1 = generate_array(ARRAY_SIZE);
	double *vector2 = generate_array(ARRAY_SIZE);
	double *result_vector = (double*) malloc(ARRAY_SIZE*sizeof(double));

	// Double check vector_add is correct
	if(!verify(vector1, vector2)) {
		printf("vector_add does not match actual result\n");
		return 0;
	}
		
	// Test framework that sweeps the number of threads and times each
    // runs for iteration REPEAT
	double start_time, run_time;
    start_time = omp_get_wtime();

    for(int j=0; j<REPEAT; j++){
        vector_add(vector1, vector2, result_vector);
    }
    run_time = omp_get_wtime() - start_time;
  	printf("To add %d elements of vectots %d thread(s) took %f seconds\n", 
	  ARRAY_SIZE, omp_get_max_threads() ,run_time);

}
