#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if( rank == 0 ){
        printf("Nombre de processus est %d\n", size);
    }
    printf("Bonjour tous le monde, je suis le processus %d\n", rank);

    MPI_Finalize();
    return 0;
}