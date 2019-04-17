// --------------------------------------------------------------------------------------------
// Author: Gahan Saraiya
// GiT: http://github.com/gahan9/
// StackOverflow: https://stackoverflow.com/users/story/7664524
// Website: http://gahan9.github.io/
// --------------------------------------------------------------------------------------------
// Ring Topology for MPI processes
#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    int world_size, world_rank;

    MPI_Init( &argc, &argv );
    MPI_Comm_size( MPI_COMM_WORLD, &world_size );
    MPI_Comm_rank( MPI_COMM_WORLD, &world_rank );

	int token;
	if (world_rank != 0) {
	    MPI_Recv(&token, 1, MPI_INT, world_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	    printf("[process-%d] I received token `%d` from process %d\n", world_rank, token, world_rank-1);
	} 

	else {
	    // Set the token's value if you are process 0
	    token = 2020;
	}

	MPI_Send(&token, 1, MPI_INT, (world_rank + 1) % world_size, 0, MPI_COMM_WORLD);

	// Now process 0 can receive from the last process.
	if (world_rank == 0) {
	    MPI_Recv(&token, 1, MPI_INT, world_size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("[process-%d] I received token `%d` from process %d\n", world_rank, token, world_size-1);
	}
	
    MPI_Finalize();
    return 0;
}