#include <stdio.h>
#include <mpi.h>

#define CENTRAL_BANK 0
#define BANK_1 1
#define BANK_2 2
#define BANK_3 3

int main(int argc, char **argv) {
	MPI_Init(NULL, NULL);

	int rank, size;
	
	MPI_Comm_size(MPI_COMM_WORLD, &size); //get number of processes
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); //get my process id

	if (size < 4) {
        fprintf(stderr, "we need 3 banks and 1 central bank, but have only %d\n", size);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

	printf ("Hello World from rank %d\n", rank);
	if (rank == CENTRAL_BANK) {
		int data[2];
		MPI_Status status;
		
		MPI_Recv(
		/* data         = */ data,
		/* count        = */ 2,
		/* datatype     = */ MPI_INT,
		/* source       = */ MPI_ANY_SOURCE,
		/* tag          = */ 0,
		/* communicator = */ MPI_COMM_WORLD,
		/* status       = */ &status
		);
		
		int destination_bank = data[0];
		int transfer_sum = data[1];
		
		MPI_Send(
			/* data         = */ &transfer_sum,
			/* count        = */ 1,
			/* datatype     = */ MPI_INT,
			/* destination  = */ destination_bank,
			/* tag          = */ 0,
			/* communicator = */ MPI_COMM_WORLD
		);
		
		printf("central bank sent sum %d\n to bank %d\n", transfer_sum, destination_bank);
	} else {
		int transfered_sum;
		MPI_Recv(
		/* data         = */ &transfered_sum,
		/* count        = */ 1,
		/* datatype     = */ MPI_INT,
		/* source       = */ MPI_ANY_SOURCE,
		/* tag          = */ 0,
		/* communicator = */ MPI_COMM_WORLD,
		/* status       = */ &status
		);
		
		printf("bank %d got sum: %d\n", transfered_sum);
	}		
	
	MPI_Finalize();

    return 0;
}
