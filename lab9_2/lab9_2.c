#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <time.h>
#include <mpi.h>

#define JOHN_SILVER_CAMP 0

int hear_answer_from_pirate() {
    int pirate_section;
    MPI_Status status;

    MPI_Recv(
            /* data         = */ &pirate_section,
            /* count        = */ 1,
            /* datatype     = */ MPI_INT,
            /* source       = */ MPI_ANY_SOURCE,
            /* tag          = */ 0,
            /* communicator = */ MPI_COMM_WORLD,
            /* status       = */ &status
            );

    return pirate_section;
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

    int island_section = rank;
    int sections_number = size;

    bool treasure_already_found = false;

    if (island_section == JOHN_SILVER_CAMP) {
        int section_with_treasure = rand() % sections_number; 
        printf("Treause is at section %d but the pirates do not know this yet.\n", section_with_treasure);
        int sections_to_search = sections_number;

        while(sections_to_search > 0) {
            --sections_to_search;

            int pirate_section = hear_answer_from_pirate();

            bool is_treasure_found = pirate_section == section_with_treasure;

            if(is_treasure_found) {
                printf("Pirate from section %d has returned with treasure!\n", pirate_section);
                treasure_already_found = is_treasure_found;
            } else if (treasure_already_found) {
                printf("pirate from section %d has not found anything, but everyone is celebrating already.\n", pirate_section);
            } else {
                printf("pirate from section %d has returned with nothing. John Silver is getting angry.\n", pirate_section);
            }
        }
    } else {
        printf("Pirate has ventured deeper into island's territory to explore section %d.\n", island_section);

        MPI_Send(
                /* data         = */ &island_section,
                /* count        = */ 1,
                /* datatype     = */ MPI_INT,
                /* destination  = */ JOHN_SILVER_CAMP,
                /* tag          = */ 0,
                /* communicator = */ MPI_COMM_WORLD
                );
    }	

    MPI_Finalize();
    
    return 0;
}
