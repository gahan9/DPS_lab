// --------------------------------------------------------------------------------------------
// Author: Gahan Saraiya
// GiT: http://github.com/gahan9/
// StackOverflow: https://stackoverflow.com/users/story/7664524
// Website: http://gahan9.github.io/
// --------------------------------------------------------------------------------------------
// Ring Topology for MPI processes
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define LUCKY_MAX 50
#define LUCKY_MIN 5

int main(int argc, char *argv[]) {
    int world_size, world_rank;
	int tag = 0;  // tag to determine whether to continue transfer or not
	int token = 0;  // ring token to be sent
	char hostname[20];
	int len;
	int lucky_number = atoi(argv[1]);
    MPI_Init( &argc, &argv );
    MPI_Comm_size( MPI_COMM_WORLD, &world_size );
    MPI_Comm_rank( MPI_COMM_WORLD, &world_rank );
	MPI_Get_processor_name(hostname, &len);

	while(tag == 0){
		/* Terminate ring communication when tag changes */
		if (world_rank != 0) {
			MPI_Recv(&token, 1, MPI_INT, world_rank - 1, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			//printf("[%s-process-%d] I got value `%d` from process %d\n", hostname, world_rank, token, world_rank-1);
		} 
		if (token >= lucky_number) {
			tag = 1;
			printf("***termination***\n");
			// MPI_Finalize();
			MPI_Abort(MPI_COMM_WORLD, 0);
		}
		else {
			token++;
			printf(">>>> %s-process-%d] I got value `%d` from process %d\n", hostname, world_rank, token, world_size-1);
			MPI_Send(&token, 1, MPI_INT, (world_rank + 1) % world_size, tag, MPI_COMM_WORLD);
		}

		// Now process 0 can receive from the last process.
		if (world_rank == 0) {
			// if (tag != 1) {
				MPI_Recv(&token, 1, MPI_INT, world_size - 1, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				printf("[%s-process-%d] I got value `%d` from process %d\n", hostname, world_rank, token, world_size-1);
			// }
		}
	}
    MPI_Finalize();
    return 0;
}