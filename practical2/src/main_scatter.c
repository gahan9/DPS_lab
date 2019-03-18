// --------------------------------------------------------------------------------------------
// Author: Gahan Saraiya
// GiT: http://github.com/gahan9/
// StackOverflow: https://stackoverflow.com/users/story/7664524
// Website: http://gahan9.github.io/
// --------------------------------------------------------------------------------------------
// Setup MPI and execute sample code given in MPI src.
// Code should print Computer machine name and rank id for each process.
// Find command to set fix process per node.
#DEFINE ARR_RANGE 20
#DEFINE SUB_ARR_RANGE 4
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
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int data;
    int *arr= (int *) malloc(sizeof(int) * ARR_RANGE);
    int *sub_arr= (int *) malloc(sizeof(int) * SUB_ARR_RANGE);
    // Task 3: Broadcast Data
    if (world_rank == 0){
        // Master Process
        // printf("***I'm The master!! Kneel before your master***\n");
        // for detail refer http://mpitutorial.com/tutorials/mpi-broadcast-and-collective-communication/
        data = 100;
        for(int i=0; i<ARR_RANGE; i++){
            arr[i] = i;
        }
        MPI_Get_processor_name(processor_name, &name_len);
        // Task 1: printing processor name
        printf("[%s-process:%d] broadcasting data %d\n", processor_name, world_rank, data);
        double start = MPI_Wtime();
        MPI_Scatter(
            arr,                 // void* send_data,
            ARR_RANGE,           // int send_count,
            MPI_INT,             // MPI_Datatype send_datatype,
            sub_arr,             // void* recv_data,
            SUB_ARR_RANGE,       // int recv_count,
            MPI_INT,             // MPI_Datatype recv_datatype,
            0,                   // int root,
            MPI_COMM_WORLD       // MPI_Comm communicator
        )
        double end = MPI_Wtime();
        // Task 2: Time measure
        printf("[%s-process:%d] Time Elapsed: %lf\n", processor_name, world_rank, end - start);
    }
    else {
        // Node/Slave Processes
        double start = MPI_Wtime();
        
        MPI_Gather(
            arr,                 // void* send_data,
            ARR_RANGE,           // int send_count,
            MPI_INT,             // MPI_Datatype send_datatype,
            sub_arr,             // void* recv_data,
            SUB_ARR_RANGE,       // int recv_count,
            MPI_INT,             // MPI_Datatype recv_datatype,
            0,                   // int root,
            MPI_COMM_WORLD       // MPI_Comm communicator
        )

        double end = MPI_Wtime();
        MPI_Get_processor_name(processor_name, &name_len);
        // Task 1: printing processor name
        printf("[%s-process:%d] received data %d from master\n", processor_name, world_rank, data);
        printf("[%s-process:%d] Time Elapsed: %lf\n", processor_name, world_rank, end - start);
    }

    // Finalize the MPI environment. No more MPI calls can be made after this
    MPI_Finalize();
}
