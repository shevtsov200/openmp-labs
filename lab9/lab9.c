#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#define CENTRAL_BANK 0
#define BANK_1 1
#define BANK_2 2
#define BANK_3 3

#define MAX_TRANSACTIONS 1

int main(int argc, char **argv) {
    MPI_Init(NULL, NULL);

    int rank, size;

    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (size < 4) {
        fprintf(stderr, "we need 3 banks and 1 central bank, but have only %d\n", size);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    srand(time(NULL) + rank);

    if (rank == CENTRAL_BANK) {
        while(1 == 1) {
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

            printf("CENTRAL BANK: Received transaction [destination: %d sum: %d]\n", destination_bank, transfer_sum);	


            printf("CENTRAL BANK: Sent sum %d to bank%d\n", transfer_sum, destination_bank);
            MPI_Send(
                    /* data         = */ &transfer_sum,
                    /* count        = */ 1,
                    /* datatype     = */ MPI_INT,
                    /* destination  = */ destination_bank,
                    /* tag          = */ 0,
                    /* communicator = */ MPI_COMM_WORLD
                    );
        }

    } else {
        int transaction_count = 0;

        while(transaction_count < MAX_TRANSACTIONS) { 
            int transfer_sum = rand() % 100;
            int destination_bank = rand() % (4 - 1) + 1;

            int data[2];
            data[0] = destination_bank;
            data[1] = transfer_sum;

            printf("BANK%d: Sent sum %d destination %d to central bank\n", rank, transfer_sum, destination_bank);
            MPI_Send(
                    /* data         = */ &data,
                    /* count        = */ 2,
                    /* datatype     = */ MPI_INT,
                    /* destination  = */ CENTRAL_BANK,
                    /* tag          = */ 0,
                    /* communicator = */ MPI_COMM_WORLD
                    );
            ++transaction_count;
        }		

        while(1==1){
            int transfered_sum;
            MPI_Status status;

            MPI_Recv(
                    /* data         = */ &transfered_sum,
                    /* count        = */ 1,
                    /* datatype     = */ MPI_INT,
                    /* source       = */ MPI_ANY_SOURCE,
                    /* tag          = */ 0,
                    /* communicator = */ MPI_COMM_WORLD,
                    /* status       = */ &status
                    );

            printf("BANK%d: Received sum: %d\n", rank, transfered_sum);
        }
    }	
    MPI_Finalize();

    return 0;
}
