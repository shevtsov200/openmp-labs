#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#define JOHN_SILVER 0

#define ISLAND_MAX_SECTIONS 10

int ask_pirates_who_is_free() {
    int free_pirate_rank;
    MPI_Status status;

    MPI_Recv(
            /* data         = */ &free_pirate_rank,
            /* count        = */ 1,
            /* datatype     = */ MPI_INT,
            /* source       = */ MPI_ANY_SOURCE,
            /* tag          = */ 0,
            /* communicator = */ MPI_COMM_WORLD,
            /* status       = */ &status
            );

    return free_pirate_rank;
}

void send_pirate_to_section(int island_section, int pirate_rank) {
    MPI_Send(
            /* data         = */ &island_section,
            /* count        = */ 1,
            /* datatype     = */ MPI_INT,
            /* destination  = */ pirate_rank,
            /* tag          = */ 0,
            /* communicator = */ MPI_COMM_WORLD
            );
}

bool hear_answer_of_pirate() {
    bool is_treasure_found;
    MPI_Status status;

    MPI_Recv(
            /* data         = */ &is_treasure_found,
            /* count        = */ 1,
            /* datatype     = */ MPI_C_BOOL,
            /* source       = */ MPI_ANY_SOURCE,
            /* tag          = */ 0,
            /* communicator = */ MPI_COMM_WORLD,
            /* status       = */ &status
            );

    return free_pirate_rank;
}

int main(int argc, char **argv) {
    MPI_Init(NULL, NULL);

    int rank, size;

    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (size < 2) {
        fprintf(stderr, "we need at least John Silver and 1 pirate, but we have: %d\n", size);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    srand(time(NULL) + rank);

    if (rank == JOHN_SILVER) {
        int section_with_treasure = rand() % ISLAND_MAX_SECTIONS; 

        int section_to_search;
        for(section_to_search = 0; section_to_search < ISLAND_MAX_SECTIONS; ++section_to_search) {
            int free_pirate_rank = ask_pirates_who_is_free(); 
            send_pirate_to_section(section_to_search, free_pirate_rank);
            bool is_treasure_found = hear_answer_of_pirate();
        }
    } else {
        int transaction_count = 0;

        while(transaction_count < MAX_TRANSACTIONS) { 
            int transfer_sum = rand() % 100;
            int destination_bank = rand() % (size - 1) + 1;

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

        while(1){
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
