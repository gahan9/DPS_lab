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
    scanf("%d", &number_of_data);
    printf("Number of data to read: %d\n", number_of_data);
    // struct Record records[number_of_data];
    int years[number_of_data];
    int amount[number_of_data];

    for(int i=0; i<number_of_data; i++){
        scanf("%d", &years[i]);
        scanf("%d", &amount[i]);
    }
    printf("Year \t Amount\n");
    for(int i=0; i<number_of_data; i++){
        printf("%d \t %d\n", years[i], amount[i]);
    }
    /*
    Completion of input reading
    */
    // MPI variables
    int dest, no_of_processes, rank;
    MPI_Status status;
    // MPI setup
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &no_of_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);



    return 0;
}
