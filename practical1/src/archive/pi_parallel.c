// --------------------------------------------------------------------------------------------
// Author: Gahan Saraiya
// GiT: http://github.com/gahan9/
// StackOverflow: https://stackoverflow.com/users/story/7664524
// Website: http://gahan9.github.io/
// --------------------------------------------------------------------------------------------
// Making code sequential code to parallel using openmp
// Do speedup calculation -- Sequential/parallel
// Show profiling and total execution time
// :: sum of two arrays
//compute the sum of two arrays in parallel 

#include <stdlib.h>
#include <stdio.h>
#include "omp.h"

int main(int argc, char *argv[]) {
    int i, count; /* points inside the unit quarter circle */
    unsigned short xi[3]; /* random number seed */
    int samples; /* samples Number of points to generate */
    double x,y; /* Coordinates of points */
    double pi; /* Estimate of pi */
    samples = atoi(argv[1]);
    #pragma omp parallel
    {
        xi[0] = 1; /* These statements set up the random seed */
        xi[1] = 1;
        xi[2] = omp_get_thread_num();
        count = 0;
        // printf("I am thread %d\n", xi[2]);
        #pragma omp for firstprivate(xi) private(x,y) reduction(+:count)
        for (i = 0; i < samples; i++) {
            x = erand48(xi);
            y = erand48(xi);
            if (x*x + y*y <= 1.0) 
                count++;
        }
    }
    pi = 4.0 * (double)count / (double)samples;
    printf("Count = %d, Samples = %d, Estimate of pi: %7.5f\n", count, samples, pi);
}

// int main(int argc, char *argv[]){
//     long int i, count; // count points inside unit circle
//     long int samples; // number of samples
//     double pi;
//     unsigned short xi[3] = {1, 5, 177}; // random number seed
//     double x, y;
//     samples = atoi(argv[1]);
//     count = 0;
//     for (i = 0; i < samples; i++) {
//         x = erand48(xi);
//         y = erand48(xi);
//         if (x*x + y*y <= 1.0) 
//             count++;
//     }
//     pi = 4.0*count/samples;
//     printf("Estimate of pi: %7.5f\n", pi);
// }
