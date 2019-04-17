#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int nb=10,vecteur[nb], matrice[nb][nb];
    int rank ,size;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if( rank == 0 ) {
        for( int i=0; i<nb; i++ ) {
            vecteur[i] = i+2;
            for( int j=0; j<nb; j++ ){
                matrice[i][j] = i + j + 2;
            }
        }
    }


    MPI_Finalize();
    return 0;

}
