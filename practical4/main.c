// --------------------------------------------------------------------------------------------
// Author: Gahan Saraiya
// GiT: http://github.com/gahan9/
// StackOverflow: https://stackoverflow.com/users/story/7664524
// Website: http://gahan9.github.io/
// --------------------------------------------------------------------------------------------
// Practical-4
// -----------
// Input: Year, amount
// ODD-Group (max amount)
// Find year with highest total amount (summation of all order in Year)
// Detail: Implement code to read year and amount (sorted by year) and find out
// year having highest order amount.
// EVEN-Group (number of order)
// Find year with highest number of order placed (count of all order in Year)

#include <stdio.h>
#include "mpi.h"

struct Record
{
    int year;
    float amount;
};

int main(int argc, char* argv[]){
    /*
    Input Taking
    */
    int number_of_data;
    int i;
    scanf("%d", &number_of_data);
    printf("Number of data to read: %d\n", number_of_data);
    // struct Record records[number_of_data];
    int years[number_of_data];
    int amount[number_of_data];

    for(i=0; i<number_of_data; i++){
        scanf("%d", &years[i]);
        scanf("%d", &amount[i]);
    }
    printf("Year \t Amount\n");
    for(i=0; i<number_of_data; i++){
        printf("%d \t %d\n", years[i], amount[i]);
    }
    /*
    Completion of input reading
    */
    // Variables
    int chunk;
    // Define number of chunks to be process by each processor
    int no_of_chunk = 2; // elements per chunk
    // Calculate number of chunks needs to be send
    int total_chunks = number_of_data / no_of_chunk;
    int results[total_chunks];

    // MPI variables
    int dest, no_of_processes, rank;
    MPI_Status status;
    // MPI setup
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &no_of_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        // Master Process
        if (no_of_processes - 1 < total_chunks){
            chunk = no_of_processes - 1;
        }
        else{
            chunk = 0;
        }
        for(i=1; i <= total_chunks; i++){
            // Receive years and amount

            if (chunk != 0 && chunk < total_chunks){
                chunk++;
            }
            else{
                chunk = 0;
            }
            // send next chunk if available
        }

    }
    else {
        int res[no_of_chunk];
        while(chunk !=0 ){
            // compute summation of year and amount
            // 
            prev_year = years[0];
            amt = amount[0]
            for (i=0; i < no_of_chunk; i++) {
                if (years[i] == prev_year){
                    res[prev_year]
                }
            }
            // send all year, amount pair
            MPI_Send(&res, 1, MPI_DOUBLE, dest, rank, MPI_COMM_WORLD);
            // Request next chunk
            MPI_Recv(&chunk, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        }
        
    }
    
    MPI_Finalize();
    return 0;
}
