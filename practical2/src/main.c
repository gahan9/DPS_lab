// --------------------------------------------------------------------------------------------
// Author: Gahan Saraiya
// GiT: http://github.com/gahan9/
// StackOverflow: https://stackoverflow.com/users/story/7664524
// Website: http://gahan9.github.io/
// --------------------------------------------------------------------------------------------
// Setup MPI and execute sample code given in MPI src.
// Code should print Computer machine name and rank id for each process.
// Find command to set fix process per node.

#include "mpi.h"
#include <stdio.h>

int main(int argc, char** argv) {
    // Initialize the MPI environment. The two arguments to MPI Init are not
    // currently used by MPI implementations, but are there in case future
    // implementations might need the arguments.
    MPI_Init(NULL, NULL);
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    int data;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Task 3: Broadcast Data
    if (world_rank == 0){
        // Master Process
        // printf("***I'm The master!! Kneel before your master***\n");
        // for detail refer http://mpitutorial.com/tutorials/mpi-broadcast-and-collective-communication/
        data = 100;
        MPI_Get_processor_name(processor_name, &name_len);
        printf("[%s-process:%d] broadcasting data %d\n", processor_name, world_rank, data);
        double start = MPI_Wtime();
        MPI_Bcast(
            &data,          // void* data               data variable
            1,              // int count,
            MPI_INT,        // MPI_Datatype datatype,
            0,              // int root                 process zero
            MPI_COMM_WORLD  // MPI_Comm communicator
            );
        double end = MPI_Wtime();
        printf("[master-process:%d] Time Elapsed: %lf\n", world_rank, end - start);
    }
    else {
        // Node/Slave Processes
        double start = MPI_Wtime();
        MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
        double end = MPI_Wtime();
        MPI_Get_processor_name(processor_name, &name_len);
        printf("[%s-process:%d] received data %d from master\n", processor_name, world_rank, data);
        printf("[%s-process:%d] Time Elapsed: %lf\n", processor_name, world_rank, end - start);
    }
    
    // Get the name of the processor
    MPI_Get_processor_name(processor_name, &name_len);

    // Task 1: print Computer machine name and rank id for each process.
    printf("Gratitude!!! from ``%s``, rank %d out of %d processes\n",
        processor_name, world_rank, world_size);

    // The times are local; the attribute MPI_WTIME_IS_GLOBAL may be used 
    // to determine if the times are also synchronized with each other for 
    // all processes in MPI_COMM_WORLD. 

    // Finalize the MPI environment. No more MPI calls can be made after this
    MPI_Finalize();
}
