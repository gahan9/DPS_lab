// --------------------------------------------------------------------------------------------
// Author: Gahan Saraiya
// GiT: http://github.com/gahan9/
// StackOverflow: https://stackoverflow.com/users/story/7664524
// Website: http://gahan9.github.io/
// --------------------------------------------------------------------------------------------
// Work Pool Example MPI

#include "mpi.h"
#include <stdio.h>

#define f(x)    ((x) * (x))

int main(int argc, char* argv[]){
    // MPI variables
    int dest, no_of_processes, rank;
    MPI_Status status;

    // problem variables
    int i, chunk, no_of_chunks, no_of_rects;
    double area, at, height, lower, width, total, range;
    double lower_limit, upper_limit;

    // MPI setup
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &no_of_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        // Master process
        // collect parameters
        fprintf(stderr, "No. of chunk to divide problem into:\n");
        scanf("%d", &no_of_chunks);
        fprintf(stderr, "No. of steps per chunk:\n");
        scanf("%d", &no_of_rects);
        fprintf(stderr, "Interval's low end:\n");
        scanf("%lf", &lower_limit);
        fprintf(stderr, "Interval's high end:\n");
        scanf("%lf", &upper_limit);
        printf(
            "\n============\n"
            "INPUT STATUS"
            "\n============\n"
            "Total Chunks: %d"
            "\nsteps per chunk: %d"
            "\nInterval: %lf to %lf"
            "\n============\n"
            , no_of_chunks, no_of_rects, lower_limit, upper_limit
        );
    }

    MPI_Bcast(&no_of_chunks, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&no_of_rects, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&lower_limit, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&upper_limit, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Collect information and output result
    if (rank == 0){
        // if rank is then assign chunk, collect results, print results
        total = 0.0;
        if (no_of_processes - 1 < no_of_chunks){
            chunk = no_of_processes - 1;
        }
        else{
            chunk = 0;
        }
        for(i=1; i <= no_of_chunks; i++){
            MPI_Recv(&area, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            printf("Area for process %d, is: %f\n", status.MPI_TAG, area);
            total += area;
            if (chunk != 0 && chunk < no_of_chunks){
                chunk++;
            }
            else{
                chunk = 0;
            }
            MPI_Send(&chunk, 1, MPI_INT, status.MPI_TAG, chunk, MPI_COMM_WORLD);
        }
        printf("The area from %f to %f is: %f\n", lower_limit, upper_limit, total);
    }
    else {
        // all other processes, calculate aread for chunk and send results
        // chunk = rank > no_of_chunks?0:rank;
        if (rank > no_of_chunks) {
            chunk = 0;
        }
        else {
            chunk = rank;
        }
        while (chunk != 0) {
            // adjust problem size for subproblem
            range = (upper_limit - lower_limit) / no_of_chunks;
            width = range/no_of_rects;
            lower = lower_limit + range * (chunk - 1);
            // printf("upper_limit: %lf\n", upper_limit);
            // printf("lower_limit: %lf\n", lower_limit);
            // calculate area for this chunk
            area = 0.0;
            for (i=0; i < no_of_rects; i++){
                at = lower + i * width + width / 2.0;
                // printf("Iteration : %d \t width: %lf\n", i, at);
                height = f(at);
                area = area + width * height;
            }
            // printf("Area ------- %lf", area);
            // send results and get next chunk
            dest = 0;
            MPI_Send(&area, 1, MPI_DOUBLE, dest, rank, MPI_COMM_WORLD);
            MPI_Recv(&chunk, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        }
    }
    // finish
    MPI_Finalize();
    return 0;
}
