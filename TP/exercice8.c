#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) 
{
    int rank, size, etiquette=99, nb=1000;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if( rank > 0 ) {
        MPI_Recv(&nb, 1, MPI_INT, rank-1, etiquette, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        nb += 1;
    } 
    if( rank != size -1 ) {
        MPI_Send(&nb, 1, MPI_INT, rank+1, etiquette, MPI_COMM_WORLD);
    }
    printf("Je suis le processus %d, j'ai la valeur %d\n", rank, nb);


    MPI_Finalize();
    return 0;
}